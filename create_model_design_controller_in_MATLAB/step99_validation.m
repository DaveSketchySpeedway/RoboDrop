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
% use kalman filter to estimate model error (disturbance)
% works only for data from decentralized (siso) controller experiments

close all
clearvars -except model
clc

% PLANT = model.chip;
PLANT = model.combo;
PLOT_RAW = false;

%% EXTRACT DATA
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

start_idx = find(data.ctrl_time > cut_start_time,1,'first');
end_idx = find(data.ctrl_time > cut_end_time,1,'first');

expe.t = data.ctrl_time(start_idx:end_idx);
expe.r = data.ctrl_reference(start_idx:end_idx,1:2);
expe.e = data.ctrl_error(start_idx:end_idx,1:2);
expe.u = data.ctrl_command(start_idx:end_idx,1:2);
expe.y = data.ctrl_measure(start_idx:end_idx,1:2);

expe.r(:,3) = -( expe.r(:,1) + expe.r(:,2) ); 
expe.y(:,3) = -( expe.y(:,1) + expe.y(:,2) );
expe.u(:,2) = expe.u(:,2)./2;
expe.u(:,3) = -expe.u(:,2);

clear start_idx* end_idx cut*

%% SET UP AUGMENTED STATESPACE


n = length(PLANT.state_d);
m = length(PLANT.input);
p = length(PLANT.output);

tuning_knob = 1e2;
sensor_variance = (expe.um_per_pix ^ 2) / 12;

kalm.A = [PLANT.Ad -PLANT.Bd; zeros(m,n) eye(m,m)];
kalm.B = [PLANT.Bd; zeros(m,m)];
kalm.W = [zeros(n,m); eye(m,m)];
kalm.C = [PLANT.Cd zeros(p,m)];
kalm.Rw = tuning_knob .* eye(m,m);
kalm.Rv = sensor_variance .* eye(p,p);
kalm.Rv(3,3) = 2*sensor_variance; % y(3,:) = -(y(1,:) + y(2,:))
kalm.state = PLANT.state_d;
for i = 1:m
    kalm.state = [kalm.state; {['disturbance_ch' num2str(i)]}];
end
clear i
clear tuning_knob sensor_variance

%% RUN SIMULATION
t = expe.t;
r = expe.r';
u = expe.u';
y_m = expe.y';

[x, y] = run_statespace(...
    PLANT.Ad, PLANT.Bd, PLANT.Cd, PLANT.Dd, t, u);

[state_estimation, kalman, error,...
    state_prediction, output_prediction,...
    estimation_covariance, prediction_coveriance] =...
    run_kalman(kalm.A, kalm.B, kalm.W, kalm.C, kalm.Rw, kalm.Rv,...
    t, u, y_m);

d = state_estimation(n+1:end,:);
clear n m p

%% PLOT SIMULATION RESULTS
figure
i = 1;
subplot(2,2,2*(i-1)+1)
hold on
plot(t,r(i,:),'r-.')
plot(t,y_m(i,:),'k')
plot(t,output_prediction(i,:),'g')
title(['A) Ch' num2str(i) ' Output'])
ylim([1000 3000])
xlabel('Time [s]')
ylabel('Position [um]')
legend('exp (reference)','exp (measured)','sim (state-space)')
grid minor

i = 2;
subplot(2,2,2*(i-1)+1)
hold on
plot(t,r(i,:),'r-.')
plot(t,y_m(i,:),'k')
plot(t,output_prediction(i,:),'g')
title(['B) Ch' num2str(i) ' Output'])
ylim([1000 3000])
xlabel('Time [s]')
ylabel('Position [um]')
legend('exp (reference)','exp (measured)','sim (state-space)')
grid minor
clear i

subplot(2,2,4)
hold on
for i = 1:2
    plot(t,d(i,:))
end
clear i
title(['D) Disturbance Estimation from Kalman Filter'])
xlabel('Time [s]')
ylabel('Pressure [mbar]')
ylim([-200 200])
legend('ch1 (interface)','ch2 (droplet)')
grid minor

subplot(2,2,2)
hold on
for i = 1:2
    plot(t,u(i,:))
end
clear i
title(['C) Model and Experiment Inputs (Shifted)'])
xlabel('Time[s]')
ylabel('Pressure[mbar]')
ylim([-200 200])
legend('ch1 (interface)','ch2 (droplet)')
grid minor

all_axes = findobj(gcf,'type','axes');
linkaxes(all_axes,'x');
% xlim(all_axes(1), [86 126])
clear all_axes

clear t u x y y_m r d



%% PLOT RAW DATA
if (PLOT_RAW)
    figure
    subplot(4,1,1)
    plot(data.ctrl_time,data.ctrl_reference)
    hold on
    plot(expe.t,expe.r,'.')
    title('Controller reference')
    xlabel('time[s]')
    ylabel('position [um]')
    grid minor

    subplot(4,1,2)
    plot(data.ctrl_time,data.ctrl_measure)
    hold on
    plot(expe.t,expe.y,'.')
    title('Controller measure')
    xlabel('time[s]')
    ylabel('position [um]')
    grid minor

    subplot(4,1,3)
    plot(data.ctrl_time,data.ctrl_error)
    hold on
    plot(expe.t,expe.e,'.')
    title('Controller error')
    xlabel('time[s]')
    ylabel('position [um]')
    grid minor

    subplot(4,1,4)
    plot(data.ctrl_time,data.ctrl_command)
    hold on
    plot(expe.t,expe.u,'.')
    title('Controller command')
    xlabel('time[s]')
    ylabel('position [um]')
    grid minor

    figure
    for i = 1:size(data.improc_x,2)
        subplot(size(data.improc_x,2),1,i)
        plot(data.ctrl_time,data.ctrl_reference(:,i),'r')
        hold on
        plot(data.ctrl_time,data.ctrl_measure(:,i),'b')
        title(['Closeloop ch' num2str(i)])
        xlabel('Time[s]')
        ylabel('Position[um]')
        legend('ctrl reference','ctrl measure')
        grid minor
    end
    clear i
end
clear PLOT_RAW