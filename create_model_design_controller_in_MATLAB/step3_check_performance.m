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
% plot open loop coupling
% plot close loop coupling
% lsim close loop 
% complex sim

close all
clearvars -except  model ctrl_c ctrl_d
clc


% PLANT = model.chip;
PLANT = model.combo;
CTRL_INDEX = 3;

PLOT_FMIN = -1;
PLOT_FMAX = 5;
PLOT_RESOLUTION = 1000;

SIM_STEP_DURATION = 10;
SIM_STEP_HEIGHT = 100;

%% OPEN LOOP FREQUENCY RESPONSE
figure
plot_coupling(PLANT.Ac, PLANT.Bc, PLANT.Cc, PLANT.Dc,...
    PLANT.input, PLANT.output,...
    0, PLOT_FMIN, PLOT_FMAX, PLOT_RESOLUTION);


%% CLOSE LOOP FREQUENCY RESPONSE
cllp = ctrl_c(CTRL_INDEX);
figure
plot_coupling(cllp.Acl,cllp.Bcl,cllp.Ccl,cllp.Dcl,...
    cllp.output, cllp.output,...
    1, PLOT_FMIN, PLOT_FMAX, PLOT_RESOLUTION);
clear cllp

%% OPEN LOOP CONTINUOUS SIMULATION
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


%% OPEN LOOP DISCRETE SIMULATION
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

%% CLEAN UP
clear CTRL_INDEX PLANT
clear PLOT* SIM*


