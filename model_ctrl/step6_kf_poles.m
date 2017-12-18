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

% this script 
% 1) run experiment data from validation
% 2) compute kalman filter poles



%% ASSUME CONTROLLER HAS BEEN BUILT FOR VAILIDATION PLANTMODEL
clearvars -except model ctrl_d ctrl_c
close all
clc

%% EXTRACT FROM DATA
% load('droplet_fast_slowslow_2016_2_16_13_58_record.mat')
% cut_start_time = 65;
% cut_end_time = 133;
% expe.um_per_pix = micron_per_pixel;
% clear micron_per_pixel controller;

load('droplet_slow_slowslow_2016_2_16_13_21_record.mat')
cut_start_time = 0;
cut_end_time = 120;
expe.um_per_pix = micron_per_pixel;
clear micron_per_pixel;
clear controller

start_idx = find(data.ctrl_time > cut_start_time,1,'first');
end_idx = find(data.ctrl_time >= cut_end_time,1,'first');

expe.t = data.ctrl_time(start_idx:end_idx);
expe.r = data.ctrl_reference(start_idx:end_idx,1:2);
expe.y = data.ctrl_measure(start_idx:end_idx,1:2);

% conservation 
expe.r(:,3) = -( expe.r(:,1) + expe.r(:,2) ); 
expe.y(:,3) = -( expe.y(:,1) + expe.y(:,2) );

% zero data
for i = 1:3
    expe.r(:,i) = expe.r(:,i) - expe.r(1,i);
    expe.y(:,i) = expe.y(:,i) - expe.y(1,i);
end

% flip data to match pump
expe.r = -expe.r;
expe.y = -expe.y;

% use pump read as model input
expe.u = zeros(length(expe.t), 3);
for i = 1:3
    start_idx = find(data.pump_read_time(:,i) > cut_start_time, 1, 'first');
    end_idx = start_idx + length(expe.t) - 1;
    expe.u(:,i) = data.pump_read(start_idx:end_idx, i);
end
clear i
% start_idx = find(data.pump_write_time > cut_start_time,1,'first');
% end_idx = find(data.pump_write_time > cut_end_time,1,'first');
% expe.u = data.pump_read(start_idx:end_idx, 1:3);
clear start_idx* end_idx cut*

%% run kf
close all
clc

cidx = 3; % channel 1 and 2 are being controlled
n = length(ctrl_d(3).state);
m = length(ctrl_d(3).input);
p = length(ctrl_d(3).output);
A = ctrl_d(3).Ad;
B = ctrl_d(3).Bd;
W = ctrl_d(3).Wd;
C = ctrl_d(3).Cd;
Rm = 10;
Rd = 1e-2;
Rw = [Rm*eye(n,n), zeros(n,m); zeros(m,n), Rd*eye(m,m)];
Rv = (expe.um_per_pix ^ 2) / 12 * eye(p,p);
t = expe.t;
u = expe.u';
y = expe.y(:,1:2)';

[state_estimation, state_prediction, output_prediction,...
    estimation_covariance, prediction_covariance, kalman] =...
    run_kalman(A,B,W,C,Rw,Rv,t,u,y);

% position estimation
figure
hold on
plot(t, y, 'r')
plot(t, state_estimation(1:2,:), 'b')
title('position')
legend('exp data','exp data','offline kf','offline kf')

% input disturbance
figure
hold on
plot(t, u, 'k')
plot(t, state_estimation(end-2:end,:), 'b')
title('input disturbance')



% kalman gain
figure
for ii = 1:size(kalman,1)
    subplot(2,1,1)
    hold on
    plot(t, squeeze(kalman(ii,1,:)))
    subplot(2,1,2)
    hold on
    plot(t, squeeze(kalman(ii,2,:)))
end

K = kalman(:,:,end);
Akf = A - K*C*A;
kf_poles_d = eig(Akf);
kf_poles_c = 1/ctrl_d(cidx).Ts.*log(kf_poles_d)
ctrl_d(cidx).state_d
kf_settling_time = [ -4./real(kf_poles_c)];
kf_settling_time(6)=666;
kf_settling_time
% kf_settling_time = [ -4./real(kf_poles_c(1:2)); % displacement states 
%     -4./real(kf_poles_c(end-2:end))]%  disturbance states




