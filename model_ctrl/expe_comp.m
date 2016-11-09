close all
clc
clearvars -except model ctrl_c ctrl_d

% EXP = 'ueva_data_2016_09_08_18_18_30.csv';
% STARTTIME = 85;
% ENDTIME = 145;
% CTRL = ctrl_d(15);
% PERTURBATION = 0;  

% EXP = 'ueva_data_2016_09_08_18_18_30.csv';
% STARTTIME = 0;
% ENDTIME = 42;
% CTRL = ctrl_d(15);
% PERTURBATION = 0.2;  

% use me
EXP = 'ueva_data_2016_09_08_18_18_30.csv';
STARTTIME = 45;
ENDTIME = 80;
CTRL = ctrl_d(19);
PERTURBATION = 0;  

% EXP = 'ueva_data_2016_09_08_18_22_59.csv';
% STARTTIME = 110;
% ENDTIME = 160;
% CTRL = ctrl_d(7);
% PERTURBATION = 0;  

% % use me
% EXP = 'ueva_data_2016_09_08_18_22_59.csv';
% STARTTIME = 0;
% ENDTIME = 40;
% CTRL = ctrl_d(7);
% PERTURBATION = 0.2;  

PLANT = model.combo;
% PLANT = model.chip;

%% EXPE
data = csvread(EXP, 1, 0);

% extract
expe.t = data(:,1);
expe.dc = data(:,2:5);
expe.d = data(:,6:9);
expe.g = data(:,10:13);
expe.y = data(:,14:19);
expe.yp = data(:,20:25);
expe.yl = data(:,26:31);
expe.yoff = data(:,32:37);
expe.yraw = data(:,38:43);
expe.r = data(:,44:49);
expe.u = data(:,98:101);

% figure
% for i = 1:length(PLANT.output)
%     subplot(length(PLANT.output)/2,2,i)
%     plot(expe.t, expe.r(:,i), 'r');
%     hold on;
%     plot(expe.t, expe.y(:,i), 'b');
%     grid minor
% end
% clear i

% cut
start_index = find(expe.t > STARTTIME, 1);
end_index = find(expe.t > ENDTIME, 1);
expe.t = expe.t(start_index:end_index,:);
expe.dc = expe.dc(start_index:end_index,:);
expe.d = expe.d(start_index:end_index,:);
expe.g = expe.g(start_index:end_index,:);
expe.y = expe.y(start_index:end_index,:);
expe.yp = expe.yp(start_index:end_index,:);
expe.yl = expe.yl(start_index:end_index,:);
expe.yoff = expe.yoff(start_index:end_index,:);
expe.yraw = expe.yraw(start_index:end_index,:);
expe.r = expe.r(start_index:end_index,:);
expe.u = expe.u(start_index:end_index,:);


%% SETUP SIMU

% SIM = 'sim_luenburger_rdelay';
SIM = 'sim_luenburger';
% SIM = 'sim_kalman';
% SIM = 'sim_kalman_dcorr_external';
% SIM = 'sim_kalman_dcorr_internal';

DOUBT_SENSOR = 3; % from sensor resolution
DOUBT_MODEL = 0.01; % fast ctrl need small doubt
DOUBT_DISTURBANCE = 1e-5; % ~DOUBT_MODEL/1000
CORRECTION_MBAR_PER_S = 0.1; % don't go higher than 0.5

RESET_TIME = 0;

time = expe.t;
reference = expe.r(:,CTRL.channel_idx);

% disturbance
disturbance = zeros(length(time), length(PLANT.input));

% noise
noise = zeros(length(time), length(PLANT.output));

% plant modify
PLANT.Ac = PLANT.Ac + PLANT.Ac * PERTURBATION;
PLANT.Bc = PLANT.Bc + PLANT.Bc * PERTURBATION;

% kalman filter
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


%% RUN SIMU
open(SIM)
sim(SIM)
close_system(SIM)

clear disturbance_idx state_idx
clear DOUBT* CORRECTION*
clear Rv Rm Rd Rw WRmW WdRwWd P00 Pd00 mbar_per_ts
clear time reference disturbance noise 
clear RESET_TIME SIM

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
figure
j = 1;
for i = 1:length(PLANT.output)
    subplot(length(PLANT.output)/2,2,i)
    plot(expe.t, expe.r(:,i), 'r');
    hold on;
    plot(expe.t, expe.y(:,i), 'b');
    if (find(CTRL.outputIdx==i) > 0)
        plot(simu.tym, simu.ym(:,j), 'g');
        legend('Reference', 'Experiment', 'Simulation')
        j = j+1;
    end
    title(['ch' num2str(i) ' Displacement']);
    xlabel('Time [s]');
    ylabel('Displacement [um]');
    grid minor
end
clear i j

all_axes = findobj(gcf, 'type', 'axes');
linkaxes(all_axes, 'x');
xlim(all_axes(1), [min(expe.t), max(expe.t)]);
clear c all_axes 





