%{
Copyright 2016 David Wong

This file is part of uEVA. https://github.com/DaveSketchySpeedway/uEVA

uEVA is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

uEVA is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with uEva. If not, see <http://www.gnu.org/licenses/>
%}


% this script:
% 1) plot full plant frequency response to show coupling
% 2) plot closed loop frequency response to show decoupling
% 3) lsim continuouse and discrete close loop system
% 4) export controllers into yaml

close all
clearvars -except model ctrl_c ctrl_d
clc


PLANT = model.chip;
% PLANT = model.combo;
CTRL_INDEX = 3;

PLOT_FMIN = -1;
PLOT_FMAX = 5;
PLOT_RESOLUTION = 1000;

SIM_STEP_DURATION = 10;
SIM_STEP_HEIGHT = 100;

%% OPEN LOOP
clc
close all

% frequency response
figure
plot_coupling(PLANT.Ac, PLANT.Bc, PLANT.Cc, PLANT.Dc,...
    PLANT.input, PLANT.output,...
    0, PLOT_FMIN, PLOT_FMAX, PLOT_RESOLUTION);

% poles
ol_poles_d = eig(PLANT.Ad)
ol_poles_c = eig(PLANT.Ac)
ol_check = ol_poles_d - exp(PLANT.Ts.*ol_poles_c)
ol_settling_time = -4./real(ol_poles_c)

%% CLOSE LOOP
clc
close all

% frequency response
cllp_d = ctrl_d(CTRL_INDEX);
cllp_c = ctrl_c(CTRL_INDEX);
figure
plot_coupling(cllp_c.Acl,cllp_c.Bcl,cllp_c.Ccl,cllp_c.Dcl,...
    cllp_c.output, cllp_c.output,...
    1, PLOT_FMIN, PLOT_FMAX, PLOT_RESOLUTION);
clear cllp

% poles
cl_poles_d = eig(cllp_d.Acl)
cl_poles_c = 1/cllp_d.Ts.*log(cl_poles_d)
cllp_d.state_cl
cl_settling_time = -4./real(cl_poles_c)

%% CLOSE LOOP CONTINUOUS SIMULATION
cllp = ctrl_c(CTRL_INDEX);
t = 0:cllp.Ts:(length(cllp.output)+1)*SIM_STEP_DURATION;
r = zeros(length(t), length(cllp.output));
for j = 1:length(cllp.output)
    start_idx = 1 + j*floor( length(t)/(1+length(cllp.output)) );
    r(start_idx:end,j) = j*SIM_STEP_HEIGHT;
end
clear j start_idx
sys = ss(cllp.Acl, cllp.Bcl, cllp.Ccl, cllp.Dcl);
y = lsim(sys, r, t);
clear cllp

figure
plot(t, r, 'r--')
hold on
plot(t,y,'.');
title(['Continuous Response: Closed Loop Combination ' num2str(CTRL_INDEX)])
xlabel('Time s')
ylabel('Position um')
grid minor
clear t r y sys


%% CLOSE LOOP DISCRETE SIMULATION
cllp = ctrl_d(CTRL_INDEX);
t = 0:cllp.Ts:(length(cllp.output)+1)*SIM_STEP_DURATION;
r = zeros(length(t), length(cllp.output));
for j = 1:length(cllp.output)
    start_idx = 1 + j*floor( length(t)/(1+length(cllp.output)) );
    r(start_idx:end,j) = j*SIM_STEP_HEIGHT;
end
clear j start_idx
sys = ss(cllp.Acl, cllp.Bcl, cllp.Ccl, cllp.Dcl, cllp.Ts);
y = lsim(sys, r, t);
% [x, y] = run_statespace(...
%     cllp.Acl, cllp.Bcl, cllp.Ccl, cllp.Dcl, t, r');
clear x cllp

figure
plot(t,r,'r--');
hold on
plot(t,y,'.');
title(['Discrete Response: Closed Loop Combination ' num2str(CTRL_INDEX)])
xlabel('Time s')
ylabel('Position um')
grid minor
clear t r y sys

%% CREATE YAML FILE

filename = strrep(ctrl_d(1).name, 'model', 'ctrl');
filename = [filename '.yaml'];
file = fopen(filename, 'w');
fprintf(file, '%%YAML:1.0\n');
fprintf(file, 'numCtrl: %d\n', length(ctrl_d));
fprintf(file, 'samplePeriod: %e\n', model.chip.Ts);
fprintf(file, 'numPlantState: %d\n', length(model.chip.state_d));
fprintf(file, 'numPlantInput: %d\n', length(model.chip.input));
fprintf(file, 'numPlantOutput: %d\n', length(model.chip.output));

%% PARSE EACH CONTROLLER
for i = 1:length(ctrl_d)
    fprintf(file, 'ctrl %d: \n', i-1); % ctrl 0 indexing
    
    CTRL = ctrl_d(i);
    fprintf(file, '  uncoUnob: %d\n', CTRL.unco_unob);
    fprintf(file, '  n: %d\n', CTRL.n);
    fprintf(file, '  m: %d\n', CTRL.m);
    fprintf(file, '  p: %d\n', CTRL.p);
    % matrix of decimal notation
    matrixNames = {'outputIdx','stateIdx'};
    for j = 1:length(matrixNames)
        matrixName = matrixNames{j};
        matrix = CTRL.(matrixName)'; % col first linear indexing
        [cols, rows] = size(matrix);
        fprintf(file, '  %s: !!opencv-matrix\n', matrixName);
        fprintf(file, '    rows: %d\n', rows);
        fprintf(file, '    cols: %d\n', cols);
        fprintf(file, '    dt: u\n'); % data type = unsigned char
        fprintf(file, '    data: [ ');
        for k = 1:rows*cols
            fprintf(file, '%d', matrix(k)-1 ); % channel 0 indexing
            if (k == rows*cols)
                break;
            end
            fprintf(file, ', ');
            if mod(k,cols) == 0
                fprintf(file, '\n            ');
            end
        end
        clear k cols rows matrix
        fprintf(file,' ]\n');
    end
    clear j
    % matrix of exponential notation 
    matrixNames = {'A','B','C','D','K1','K2','H', 'Ad', 'Bd','Cd','Wd'};
    for j = 1:length(matrixNames)
        matrixName = matrixNames{j};
        matrix = CTRL.(matrixName)'; % col first linear indexing
        [cols, rows] = size(matrix);
        fprintf(file, '  %s: !!opencv-matrix\n', matrixName);
        fprintf(file, '    rows: %d\n', rows);
        fprintf(file, '    cols: %d\n', cols);
        fprintf(file, '    dt: d\n'); % data type = double
        fprintf(file, '    data: [ ');
        for k = 1:rows*cols
            fprintf(file, '%.12e', matrix(k)); % 12 decimal places
            if (k == rows*cols)
                break;
            end
            fprintf(file, ', ');
            if mod(k,cols) == 0
                fprintf(file, '\n            ');
            end
        end
        clear k cols rows matrix
        fprintf(file,' ]\n');
    end
    clear j
end
clear i

fclose(file);
clear CTRL_INDEX PLANT
clear PLOT* SIM*
clear filename file CTRL
clear matrixName matrixNames ans

