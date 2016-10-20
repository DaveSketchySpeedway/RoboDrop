clear
clc
close all

FIT_DATA = 'time_domain_data_150-250_step.mat';
% FIT_DATA = 'time_domain_data_150-250_ramp2s.mat';
% FIT_DATA = 'time_domain_data_150-250_ramp05s.mat';
% FIT_DATA = 'time_domain_data_150-250_ramp025s.mat';

% TEST_DATA = 'time_domain_data_150-250_step.mat';
TEST_DATA = 'time_domain_data_150-250_ramp2s.mat';
% TEST_DATA = 'time_domain_data_150-250_ramp05s.mat';
% TEST_DATA = 'time_domain_data_150-250_ramp025s.mat';


%% load data and calculate sample period and delay
load(FIT_DATA)

for i = 1:length(data) 
    for k = 1:length(data(i).in_time)
        if isnan(data(i).in_value(k))
            data(i).in_value(k) = [];
            data(i).in_time(k) = [];
            data(i).out_value(k) = [];
            data(i).out_time(k) = [];
        end
    end
end
clear i k cut

write_read_delay = zeros(size(data));
sample_period = zeros(size(data));
for i = 1:length(data)
    delays = data(i).in_time - data(i).out_time;
    write_read_delay(i) = mean(delays);
    sample_period(i) = max(data(i).in_time)/length(data(i).in_time);
    clear delays
end
clear i

%% least square
Ts = 0.1;
order = 3;
den = zeros(order + 1,length(data));
num = zeros(order + 1,length(data));
for i = 1:length(data)
    ot = data(i).out_time;
    v = data(i).out_value;
    u = zeros(size(ot));
    for k = 1:length(ot) % u is input interpolated at out_time
        u(k) = interp1(data(i).in_time,data(i).in_value,...
            ot(k),'linear','extrap');        
    end
    clear k
    
    [a,b,v_check,residue,sys,sys_d] = least_square_dynamic(u, v, Ts, order);
    den(:,i) = [1; a'];
    num(:,i) = b';
    ch(i).a = a;
    ch(i).b = b;
    ch(i).v_check = v_check;
    ch(i).residue = residue;
    ch(i).sys = sys;
    ch(i).sys_d = sys_d;
    ch(i).ot = ot;
    ch(i).u = u;
    ch(i).v = v;
    clear a b v_check residue sys sys_d u v ot
end
clear i sample_period write_read_delay


%% transfer function (average)
sys_d = tf(mean(num,2).',mean(den,2).',Ts);
sys = d2c(sys_d,'zoh');
clear num den

%% state space (individual)
nfctm = 3; % number of channel to model
A = zeros(nfctm*order);
B = zeros(nfctm*order, nfctm);
C = zeros(nfctm, nfctm*order);
D = zeros(nfctm, nfctm);
pump_state = [];
for i = 1:nfctm
    [a,b,c,d] = ssdata(ss(ch(i).sys_d));
    A(i*order-order+1:i*order, i*order-order+1:i*order) = a;
    B(i*order-order+1:i*order, i) = b;
    C(i, i*order-order+1:i*order) = c;
    D(i, i) = d;
    for j = 1:order
        pump_state = [pump_state; {['pump_ch' num2str(i) '_k-' num2str(j-1)]}];
    end
    clear j
end
ss_d = ss(A,B,C,D,Ts);
save('pump_sysid_time.mat','sys_d','sys',...
    'A', 'B', 'C', 'D', 'Ts', 'pump_state');
clear i a b c d A B C D

%% plot to check fit
close all
figure
clear data
load(FIT_DATA)

% make uniform length input vector for ss lsim
l = 1e12;
for i = 1:nfctm % redneck min fnc
    if l > length(data(i).out_time)
        l = length(data(i).out_time);
    end
end
u = zeros(l,nfctm);
ot = zeros(l,nfctm);
for i = 1:nfctm
    ot(:,i) = data(i).out_time(1:l);
    for k = 1:length(ot) % u is input interpolated at out_time
        u(k,i) = interp1(data(i).in_time,data(i).in_value,...
            ot(k,i),'linear','extrap');        
    end
    clear k
end
clear i l

v_ssd = lsim(ss_d,u);

% plot
for i = 1:length(data)
    subplot(length(data),1,i)
    hold on
    plot(data(i).in_time,data(i).in_value,'r--') 
    plot(data(i).out_time,data(i).out_value, 'k+')
    v_avg = lsim(sys_d,u(:,1));
    plot(ot(:,1),v_avg,'b') % transfer function avg
%     plot(ch(i).ot,ch(i).v_check,'y') % least square individual
    if i <= nfctm
%         plot(ot(:,i),v_ssd(:,i), 'g') % state space individual
    end
%     legend('command','measurement','tf avg fit','LS indivi fit', 'ss indivifit')
    legend('Command', 'Measure', 'Model')
    title(['Pump Fit Order=' num2str(order) ' (ch' num2str(i) ')'])
    xlabel('Time [s]')
    ylabel('Pressure [mbar]')

    grid minor
end
clear i 
all_axes = findobj(gcf, 'type', 'axes');
linkaxes(all_axes, 'x');

%% plot fit against other data set
close all
clear data
figure



load(FIT_DATA)
% make uniform length input vector for ss lsim
l = 1e12;
for i = 1:nfctm % redneck min fnc
    if l > length(data(i).out_time)
        l = length(data(i).out_time);
    end
end
u = zeros(l,nfctm);
ot = zeros(l,nfctm);
for i = 1:nfctm
    ot(:,i) = data(i).out_time(1:l);
    for k = 1:length(ot) % u is input interpolated at out_time
        u(k,i) = interp1(data(i).in_time,data(i).in_value,...
            ot(k,i),'linear','extrap');        
    end
    clear k
end
clear i l

i = 1;
v_ssd = lsim(ss_d,u);
subplot(2,1,1)
plot(data(i).in_time,data(i).in_value,'r--') 
hold on
plot(data(i).out_time,data(i).out_value, 'k+')
if i <= nfctm
    plot(ot(:,i),v_ssd(:,i), 'b')
end
legend('Command','Measure','Model')
title(['Pump Model vs Fit Data (Ch' num2str(i) ')'])

xlabel('Time [s]')
ylabel('Pressure [mbar]')
grid minor
clear i






load(TEST_DATA)
% make uniform length input vector for ss lsim
l = 1e12;
for i = 1:nfctm % redneck min fnc
    if l > length(data(i).out_time)
        l = length(data(i).out_time);
    end
end
u = zeros(l,nfctm);
ot = zeros(l,nfctm);
for i = 1:nfctm
    ot(:,i) = data(i).out_time(1:l);
    for k = 1:length(ot) % u is input interpolated at out_time
        u(k,i) = interp1(data(i).in_time,data(i).in_value,...
            ot(k,i),'linear','extrap');        
    end
    clear k
end
clear i l

i = 1;
v_ssd = lsim(ss_d,u);
subplot(2,1,2)
plot(data(i).in_time,data(i).in_value,'r--') 
hold on
plot(data(i).out_time,data(i).out_value, 'k+')
if i <= nfctm
    plot(ot(:,i),v_ssd(:,i), 'b')
end
legend('command','measure','model')
title(['Pump Model vs Test Data (Ch' num2str(i) ')'])

xlabel('Time [s]')
ylabel('Pressure [mbar]')
grid minor
clear i


