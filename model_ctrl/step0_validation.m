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
% 1) first estimate d using kalman filter
% 2) then simulate v and y base on u-d using model

close all
clearvars -except model
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

% velocity by central difference
expe.v = zeros(size(expe.y));
for j = 1:3
    for i = 2:length(expe.t)-1
        expe.v(i,j) = (expe.y(i+1,j) - expe.y(i-1,j)) /...
            (expe.t(i+1) - expe.t(i-1)); 
    end
end
clear i j

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

% plot raw data
num_chan = size(data.ctrl_reference,2);

figure
for i = 1:num_chan
    subplot(num_chan,2,(i-1)*2+1)
    plot(data.ctrl_time, data.ctrl_reference(:,i), 'r')
    hold on
    plot(data.ctrl_time, data.ctrl_measure(:,i), 'b')
    if (i == 1)
        title('reference and measurement data')
    end
    if (i == num_chan)
        xlabel('time [s]')
    end
    ylabel('position [um]')
    grid minor

    subplot(num_chan,2, i*2)
    plot(data.ctrl_time, data.ctrl_command(:,i), 'k')
    hold on
    plot(data.pump_read_time(:,i), data.pump_read(:,i), 'k.')
    if (i == 1)
        title('command and pump data')
    end
    if (i== num_chan)
        xlabel('time [s]')
    end
    ylabel('pressure [mbar]')
    grid minor
end
all_axes = findobj(gcf,'type','axes');
linkaxes(all_axes,'x');
xlim(all_axes(1), [min(data.ctrl_time), max(data.ctrl_time)])
clear i all_axes num_chan

% plot extracted 
num_chan = size(expe.r,2);

figure
for i = 1:num_chan
    subplot(num_chan,2,(i-1)*2+1)
    plot(expe.t, expe.r(:,i), 'r')
    hold on
    plot(expe.t, expe.y(:,i), 'b')
    if (i==1)
        title('extracted r and y')
    end
    if (i == num_chan)
        xlabel('time [s]')
    end
    ylabel('position [um]')
    grid minor

    subplot(num_chan,2, i*2)
    plot(expe.t, expe.u(:,i), 'k')
    hold on
    if (i == 1)
        title('extracted u')
    end
    if (i == num_chan)
        xlabel('time [s]')
    end
    ylabel('pressure [mbar]')
    grid minor
end    
all_axes = findobj(gcf, 'type', 'axes');
linkaxes(all_axes, 'x');
xlim(all_axes(1), [min(expe.t), max(expe.t)]);
clear i all_axes num_chan



%% SET UP AUGMENTED STATESPACE
n = length(model.chip.state_d);
m = length(model.chip.input);
p = length(model.chip.output);

sensor_variance = (expe.um_per_pix ^ 2) / 12;
model_knob = 0;
disturbance_knob = 0.01;

kalm.A = [model.chip.Ad -model.chip.Bd; zeros(m,n) eye(m,m)];
kalm.B = [model.chip.Bd; zeros(m,m)];
% kalm.W = [zeros(n,m); eye(m,m)];
kalm.W = eye(n+m, n+m);
kalm.C = [model.chip.Cd zeros(p,m)];
% kalm.Rw = tuning_knob .* eye(m,m);
kalm.Rw = [model_knob .* eye(n,n), zeros(n,m); zeros(m,n), disturbance_knob.* eye(m,m)];
kalm.Rv = sensor_variance .* eye(p,p);
kalm.Rv(3,3) = 2*sensor_variance; % y(3,:) = -(y(1,:) + y(2,:))
kalm.state = model.chip.state_d;
for i = 1:m
    kalm.state = [kalm.state; {['disturbance_ch' num2str(i)]}];
end

clear i n m p
clear model_knob disturbnce_knob sensor_variance

%% VALIDATION BY SIMULATION
vali.t = expe.t;
vali.u = expe.u';
vali.r = expe.r';
vali.y = expe.y';
vali.v = expe.v';

[vali.xe, vali.xp, vali.yp, vali.pe, vali.pp, vali.kg] =...
    run_kalman(kalm.A, kalm.B, kalm.W, kalm.C, kalm.Rw, kalm.Rv,...
    vali.t, vali.u, vali.y);

vali.de = zeros(size(vali.u));
vali.ud = zeros(size(vali.u));
for i = 1:size(vali.ud,1)
    vali.de(i,:) = vali.xe(end-size(vali.u,1)+i,:);
    vali.ud(i,:) = vali.u(i,:) - mean(vali.de(i,:));
%     sim.ud(i,:) = sim.u(i,:) - sim.de(i,:);
end

[deleteme, vali.vo] = run_statespace(...
    model.raw.a, model.raw.b, model.raw.c, model.raw.d, vali.t, vali.ud);

[deleteme, vali.yo] = run_statespace(...
    model.chip.Ad, model.chip.Bd, model.chip.Cd, model.chip.Dd, vali.t, vali.ud);

clear deleteme

%% PLOT SIMULATION RESULTS
% kalman estimations
figure
for i = 1:size(vali.r,1)
    
    subplot(size(vali.r,1),2,(i-1)*2+1)
    plot(vali.t, vali.r(i,:), 'r')
    hold on
    plot(vali.t, vali.y(i,:), 'b.')
    plot(vali.t, vali.yp(i,:), 'c.')
    if (i == 1)
        title('r(red) vs y(blue) vs yp(cyan)')
    end
    if (i == size(vali.r,1))
        xlabel('time [s]')
    end
    ylabel('position [um]')
    grid minor
        
    if i <= size(vali.u)
        subplot(size(vali.r,1),2,i*2)
        plot(vali.t, vali.u(i,:), 'k.')
        hold on
        plot(vali.t, vali.de(i,:), 'g.')
        if (i == 1)
            title('u(black) and de(green)')
        end
        if (i == size(vali.r,1))
            xlabel('time [s]')
        end
        ylabel('pressure [mbar]')
        grid minor
    end    
end
all_axes = findobj(gcf, 'type', 'axes');
linkaxes(all_axes, 'x');
xlim(all_axes(1), [min(vali.t), max(vali.t)]);
clear i all_axes 

% open loop simulation
figure
for i = 1:size(vali.r,1)
    subplot(size(vali.r,1),3, (i-1)*3+1)
    plot(vali.t, vali.r(i,:), 'r')
    hold on
    plot(vali.t, vali.y(i,:), 'b.')
    plot(vali.t, vali.yo(i,:), 'c.')
    if (i==1)
%         title('r(red) vs y(blue) vs yo(cyan)')
        title('Displacement')
    end
    if (i==size(vali.r,1))
        xlabel('time [s]')
    end
    ylabel('position [um]')
    grid minor
    legend('reference','simulation','experiment');
    
    subplot(size(vali.r,1),3,(i-1)*3+2)
    plot(vali.t, vali.v(i,:), 'r')
    hold on
    plot(vali.t, vali.vo(i,:), 'm.')
    if (i == 1)
%         title('v(red) vs vo(dots)')
        title('Velocity')
    end
    if (i == size(vali.r,1))
        xlabel('time [s]')
    end
    ylabel('velocity [um/s]')
    grid minor
    legend('experiment', 'simulation');
    
    if i <= size(vali.ud)
        subplot(size(vali.r,1),3,3*i)  
        plot(vali.t, vali.ud(i,:), 'k.')
        if (i == 1)
            title('u - d')
        end
        if (i == size(vali.r,1))
            xlabel('time [s]')
        end
        ylabel('pressure [mbar]')
        grid minor
    end
end
all_axes = findobj(gcf, 'type', 'axes');
linkaxes(all_axes, 'x');
xlim(all_axes(1), [min(vali.t), max(vali.t)]);
clear i all_axes 
    
    
    
    






