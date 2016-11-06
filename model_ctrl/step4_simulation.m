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
% 1) effect of LQR chip, PLANT combo
% 2) effect of noise and disturbance
% 3) state resets
% 4) attempt to cancel disturbance

close all
clc
clearvars -except model ctrl_c ctrl_d

% SIM = 'sim_luenburger_rdelay';
% SIM = 'sim_luenburger';
% SIM = 'sim_kalman';
SIM = 'sim_kalman_dcorr_external';
% SIM = 'sim_kalman_dcorr_internal';

DOUBT_SENSOR = 3; % from sensor resolution
DOUBT_MODEL = 0.01; % fast ctrl need small doubt
DOUBT_DISTURBANCE = 1e-5; % ~DOUBT_MODEL/1000
CORRECTION_MBAR_PER_S = 0.1; % don't go higher than 0.5
    
PLANT = model.combo;
% PLANT = model.chip;

CTRL = ctrl_d(15);

PERTURBATION = 0;    
REFERENCE_STEP_DURATION = 10;
REFERENCE_STEP_HEIGHT = 500;
NOISE_STEP_HEIGHT = 0;
DISTURBANCE_STEP_HEIGHT = -50;

RESET_TIME = REFERENCE_STEP_DURATION*(1 + length(CTRL.output));
%% SIGNAL GENERATION
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
    disturbance(:,j) = ones(length(time), 1) * (2*rand-1) * DISTURBANCE_STEP_HEIGHT;
end
clear j

% noise
noise = zeros(length(time), length(PLANT.output));
for j = 1:length(PLANT.output)
    half_step_length = floor( length(time)/(1+length(CTRL.output))/2 );
    start_idx = (2*(j-1)+1)*half_step_length;
    noise(start_idx:end,j) = NOISE_STEP_HEIGHT;
end
clear j start_idx half_step_length

clear DISTURBANCE* NOISE* REFERENCE*
%% PERTURB PLANT
PLANT.Ac = PLANT.Ac + PLANT.Ac * PERTURBATION;
PLANT.Bc = PLANT.Bc + PLANT.Bc * PERTURBATION;

clear PERTURBATION
%% KALMAN NOISE
state_idx = 1:CTRL.n;
j = 1;
for i = CTRL.n+1:length(CTRL.state_d)
    disturbance_idx(j) = i;
    j = j + 1;
end
clear i j

Rv = eye(CTRL.p,CTRL.p)*(DOUBT_SENSOR^2/12);
Rm = eye(CTRL.n,CTRL.n)*DOUBT_MODEL;
Rd = eye(CTRL.m,CTRL.m)*DOUBT_DISTURBANCE;
Rw = [Rm, zeros(CTRL.n, CTRL.m); zeros(CTRL.m, CTRL.n), Rd];
WRmW = eye(CTRL.n, CTRL.n) * Rm * eye(CTRL.n, CTRL.n)';
WdRwWd = CTRL.Wd * Rw * CTRL.Wd';
P00 = eye(CTRL.n,CTRL.n)*1e3;
Pd00 = eye(CTRL.n + CTRL.m, CTRL.n + CTRL.m)*1e3;

mbar_per_ts = CORRECTION_MBAR_PER_S * CTRL.Ts;

%% SIM
open(SIM)
sim(SIM)

clear disturbance_idx state_idx
clear DOUBT* CORRECTION*
clear Rv Rm Rd Rw WRmW WdRwWd P00 Pd00 mbar_per_ts
clear time reference disturbance noise 
clear RESET_TIME SIM
%% SAVE
simu.r = r.signals.values;
simu.tr = r.time;
simu.u = u.signals.values;
simu.tu = u.time;
simu.d = d.signals.values;
simu.td = d.time;
simu.n = n.signals.values;
simu.tn = n.time;
simu.y = y.signals.values;
simu.ty = y.time;
simu.ym = ym.signals.values;
simu.tym = ym.time;
simu.yp = yp.signals.values;
simu.typ = yp.time;
simu.xe = xe.signals.values;
simu.txe = xe.time;
simu.z = z.signals.values;
simu.tz = z.time;
try
    simu.de = de.signals.values;
    simu.tde = de.time;
    simu.dc = dc.signals.values;
    simu.tdc = dc.time;
catch
end
clear ans




clear d n r tout u y ym yp xe z de 
%% PLOT
% close all
% 
% figure
% i = 1;
% for c = 1:size(simu.y,2)
%     
%     subplot(size(simu.y,2),2,(c-1)*2+1)
%     plot(simu.ty, simu.y(:,c), 'b')
%     hold on
%     if (find(CTRL.channel_idx == c))
%         plot(simu.tr, simu.r(:,i), 'r')
%         plot(simu.tym, simu.ym(:,i), 'b.')
%         plot(simu.typ, simu.yp(:,i), 'c.')
%         i = i + 1;
%     end    
%     if (c == 1)
%         title('R(red) Ym(blue) Yp(cyan)')
%     end
%     if (c == size(simu.y,2))
%         xlabel('time [s]')
%     end
%     ylabel('position [um]')
%     grid minor
%         
%     subplot(size(simu.y,2),2,c*2)
%     if (c <= size(simu.u,2))
%         plot(simu.td, simu.d(:,c), 'r')
%         hold on
%         plot(simu.tu, simu.u(:,c), 'k.')
%     end 
%     if (c == 1)
%         title('D(red) K(black)')
%     end
%     if (c == size(simu.y,2))
%         xlabel('time [s]')
%     end
%     ylabel('pressure [mbar]')
%     grid minor
% end
% all_axes = findobj(gcf, 'type', 'axes');
% linkaxes(all_axes, 'x');
% xlim(all_axes(1), [min(simu.tr), max(simu.tr)]);
% clear i c all_axes 
% 
% 
% figure
% i = 1;
% for c = 1:size(simu.y,2)
%     
%     subplot(size(simu.y,2),3,(c-1)*3+1)
%     plot(simu.ty, simu.y(:,c), 'b')
%     hold on
%     if (find(CTRL.channel_idx == c))
%         plot(simu.tr, simu.r(:,i), 'r')
%         plot(simu.txe, simu.xe(:,i), 'g.')
%         plot(simu.typ, simu.yp(:,i), 'c.')
% %         i = i + 1;
%     end    
%     if (c == 1)
% %         title('R(red) Yp(cyan) Xe(green)')
%         title('Displacement')
%     end
%     if (c == size(simu.y,2))
%         xlabel('time [s]')
%     end
%     ylabel('position [um]')
%     grid minor
%     legend('measurement','reference','states','prediction')
%         
%     subplot(size(simu.y,2),3,(c-1)*3+2)
%     plot(simu.ty, simu.y(:,c), 'b')
%     hold on
%     if (find(CTRL.channel_idx == c))
%         plot(simu.tr, simu.r(:,i), 'r')
%         plot(simu.tz, simu.z(:,i), 'm.')
%         i = i + 1;
%     end    
%     if (c == 1)
% %         title('R(red) Z(magenta)')
%         title('Integral Feedback')
%     end
%     if (c == size(simu.y,2))
%         xlabel('time [s]')
%     end
%     ylabel('position integral [um s]')
%     grid minor
%     legend('measurement','reference','integral states');
%     
%     subplot(size(simu.y,2),3,c*3)
%     if (c <= size(simu.u,2))
%         plot(simu.td, simu.d(:,c), 'r')
%         hold on
%         try
%             plot(simu.tde, simu.de(:,c), 'g.')
%             plot(simu.tdc, simu.dc(:,c), 'c.')
%         catch
%         end
%     end 
%     if (c == 1)
% %         title('D(red) De(green) Dc(cyan)')
%     title('Disturbance Correction')
%     end
%     if (c == size(simu.y,2))
%         xlabel('time [s]')
%     end
%     ylabel('pressure [mbar]')
%     grid minor
%     legend('disturbance','estimate','correction')
% end
% all_axes = findobj(gcf, 'type', 'axes');
% linkaxes(all_axes, 'x');
% xlim(all_axes(1), [min(simu.tr), max(simu.tr)]);
% clear i c all_axes 

%% PLOT PUBLISH
close all

figure
j = 1;
for i = 1:length(PLANT.output)
    subplot(length(PLANT.output)/2,2,i)
    plot(simu.ty, simu.y(:,i), 'b');
    hold on;
    legend('y Ouput (Invisible)')
    if (find(CTRL.outputIdx==i) > 0)
        plot(simu.tym, simu.ym(:,j), 'g.');
        plot(simu.tr, simu.r(:,j), 'r');
        legend('y Output (Invisible)', 'y Output (Visible)', 'r Reference')
        j = j+1;
    end
    title(['ch' num2str(i) ' Displacement']);
    xlabel('Time [s]');
    ylabel('Displacement [um]');
    grid minor
end
clear i

figure
for i = 1:length(PLANT.input)
    subplot(length(PLANT.input)/2,2,i)
    plot(simu.td, simu.d(:,i), 'r');
    hold on;
    plot(simu.tu, simu.u(:,i), 'k.');
    plot(simu.tde, simu.de(:,i), 'g.');
    plot(simu.tdc, simu.dc(:,i), 'b.');
    legend('d Disturbance (Static Offset)','u Command',...
        'd* Disturbance (Kalman Estimate)','dc Correction {Accumulative}');
    title(['in' num2str(i) ' Pressure']);
    xlabel('Time [s]');
    ylabel('Pressure [mbar]');
    grid minor
end
clear i







