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



% this cript run simulink model to evaluate the following:
%
% disturbance on 
% max dof: all stable, all estimage wrong
% reduced dof: dof stable, all estimage wrong
% fake: dof stable, all estimage wrong
% fake reset: estimate == mesured after reset, small fluctuation
% reduced dof reset: estimate == mesured after reset, small fluctuation
% 
% noise on
% max: all stable, dof estimate correct for noise, 
% reduced dof: all stable, dof estimate correct for noise
% fake: all stable, fake estimate wrong after noise
% fake reset: estimate == mesured after reset, no fluctuation
% reduced dof reset: estimate == mesured after reset, no fluctuation

close all
clc
clearvars -except model ctrl_c ctrl_d



% SIM = 'sim_dof';
SIM = 'sim_dof_reset';
% SIM = 'sim_fake';
% SIM = 'sim_fake_reset';
PLANT = model.combo;
% PLANT = model.chip;
% CTRL = ctrl_d(5); % red dof
CTRL = ctrl_d(7); % max dof
% CTRL = ctrl_d(63); % max dof lock

REFERENCE_STEP_DURATION = 10;
REFERENCE_STEP_HEIGHT = 500;
DISTURBANCE_STEP_HEIGHT = 0;
NOISE_STEP_HEIGHT = 100;
PERTURBATION = 0.1;

FAKE = [];
REAL = 1:length(CTRL.output);
REAL(FAKE) = [];

RESET_TIME = REFERENCE_STEP_DURATION*(1 + length(CTRL.output));



%% GEN
time = [CTRL.Ts:CTRL.Ts:REFERENCE_STEP_DURATION*(length(CTRL.output)+1)]';

% reference
reference = zeros(length(time), length(CTRL.output));
for j = 1:length(CTRL.output)
    start_idx = 1 + j*floor( length(time)/(1+length(CTRL.output)) );
    reference(start_idx:end,j) = j*REFERENCE_STEP_HEIGHT;
end
clear j start_idx

% disturbance
disturbance = zeros(length(time), length(PLANT.input));
for j = 1:length(PLANT.input)
    half_step_length = floor( length(time)/(1+length(CTRL.output))/2 );
    start_idx = (2*(j-1)+1)*half_step_length;
    disturbance(start_idx:end,j) = DISTURBANCE_STEP_HEIGHT;
end
clear j start_idx half_step_length

% noise
noise = zeros(length(time), length(PLANT.output));
for j = 1:length(PLANT.output)
    half_step_length = floor( length(time)/(1+length(CTRL.output))/2 );
    start_idx = (2*(j-1)+1)*half_step_length;
    noise(start_idx:end,j) = NOISE_STEP_HEIGHT;
end
clear j start_idx half_step_length




% figure
% subplot(2,1,1)
% plot(t,r)
% subplot(2,1,2)
% plot(t,d)
% pause 
% close all


%% PERTURB PLANT
PLANT.Ac = PLANT.Ac + PLANT.Ac * PERTURBATION;
PLANT.Bc = PLANT.Bc + PLANT.Bc * PERTURBATION;



%% SIM
open(SIM)
sim(SIM)
clear time reference disturbance noise 


%% SAVE
data.r = r.signals.values;
data.tr = r.time;
data.xe = xe.signals.values;
data.txe = xe.time;
data.ye = ye.signals.values;
data.tye = ye.time;
data.u = u.signals.values;
data.tu = u.time;
data.y = y.signals.values;
data.ty = y.time;
data.ym = ym.signals.values;
data.tym = ym.time;
data.yme = yme.signals.values;
data.tyme = yme.time;
clear t* r d xe ye u y ym yme 


%% PLOT
close all

% states
figure
subplot(3,1,1)
plot(data.tyme, data.yme)
title('ym - ye')
grid minor

subplot(3,1,2)
plot(data.txe, data.xe(:,1:length(CTRL.output)))
title('position states')
grid minor

subplot(3,1,3)
plot(data.txe, data.xe(:,length(CTRL.output)+1:end))
title('velocity and pressure states')
grid minor

% output and command
figure
subplot(3,1,[1 2])
plot(data.tr, data.r,'r--')
hold on
plot(data.tym, data.ym, 'bo')
hold on
plot(data.tye, data.ye, 'gd')
hold on
plot(data.ty, data.y, 'k')
title('output')
grid minor
reference_text = {};
for i = 1:length(CTRL.output)
    text = ['reference: ' CTRL.output{i}];
    reference_text = [reference_text, {text}];
end
clear text i
measured_text = {};
for i = 1:length(CTRL.output)
    text = ['measured: ' CTRL.output{i}];
    measured_text = [measured_text, {text}];
end
estimate_text = {};
for i = 1:length(CTRL.output)
    text = ['estimate: ' CTRL.output{i}];
    estimate_text = [estimate_text, {text}];
end
clear text i
plant_text = {};
for i = 1:length(PLANT.output)
    text = ['plant: ' PLANT.output{i}];
    plant_text = [plant_text, {text}];
end
clear text i
legend_text = [reference_text, measured_text(REAL), estimate_text, plant_text];
legend(legend_text, 'Interpreter', 'none')
clear *text

subplot(3,1,3)
plot(data.tu, data.u, '.')
title('command')
grid minor

%% CLEAN UP
clear PLANT CTRL
clear FAKE REAL
clear REFERENCE* DISTURBANCE* NOISE* PERTURBATION
clear SIM RESET_TIME




