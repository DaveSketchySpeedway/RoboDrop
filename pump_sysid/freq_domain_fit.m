close all
clear
clc

load('freq_domain_data_200-600_more_pt.mat')
freq = [signal.frequency]';
omega = 2*pi*freq;

% for f = 1:size(data,1)
%     figure;
%     for c = 1:size(data,2)
%         subplot(4,1,c)
%         hold on
%         grid minor
%     %     axis([0,2,0,1000])
%         plot(data(f,c).in_time, data(f,c).in_value, '-r.')
%         plot(data(f,c).out_time, data(f,c).out_value, 'b.')
%         title(['Channel ' num2str(c) ' at ' num2str(freq(f)) ' hz'])
%         xlabel('time[s]')
%         ylabel('pressure[mbar]')
%     end
% end
% clear f c





%% least square write
close all
write_amp = zeros(size(data));
write_phase = zeros(size(data));
write_mean = zeros(size(data));

for c = 1:size(data,2)
    figure
    for f = 1:size(data,1)
        [write_amp(f,c),write_phase(f,c),write_mean(f,c)] =...
            least_square_sin(data(f,c).in_value,data(f,c).in_time,freq(f));

        subplot(size(data,1)/2,2,f) 
        t = linspace(min([data(f,c).in_time]),max([data(f,c).in_time]),1000);
        y = write_amp(f,c)*...
            sin(omega(f).*t + write_phase(f,c)) + write_mean(f,c);
        plot(data(f,c).in_time,data(f,c).in_value,'r.')
        hold on
        plot(t, y, 'b')
%         title('Write vs Fit')
%         xlabel('time[s]')
%         ylabel('pressure[mbar]')
        if (f <=2)
            title(['Sinusoid Fit on Pump Command (ch' num2str(c) ')'])
        end
        if (f >= size(data,1) -1)
            xlabel('Time [s]')
        end
    end
end
clear f c t y

%% least square read
close all
read_amp = zeros(size(data));
read_phase = zeros(size(data));
read_mean = zeros(size(data));

for c = 1:size(data,2)
    figure
    for f = 1:size(data,1)
        [read_amp(f,c),read_phase(f,c),read_mean(f,c)] =...
            least_square_sin(data(f,c).out_value,data(f,c).out_time,freq(f));

        subplot(size(data,1)/2,2,f) 
        t = linspace(min([data(f,c).out_time]),max([data(f,c).out_time]),1000);
        y = read_amp(f,c)*...
            sin(omega(f).*t + read_phase(f,c)) + read_mean(f,c);
        plot(data(f,c).out_time,data(f,c).out_value,'r.')
        hold on
        plot(t, y, 'b')
%         title('Read vs Fit')
%         xlabel('time[s]')
%         ylabel('pressure[mbar]')
        if (f <=2)
            title(['Sinusoid Fit on Pump Measurement (ch' num2str(c) ')'])
        end
        if (f >= size(data,1) -1)
            xlabel('Time [s]')
        end
    end
end
clear f c t y

%% 2nd order (low pass + pade)
clear sys*
order = 2;
Ts = 0.1;
delay = 0.05;
pole_real = 8;
k = pole_real;
sys = tf([-delay/2 1],[delay/2 1]) * k * tf(1,[1 pole_real]);
sys_d = c2d(sys,Ts,'zoh');
clear pole* k

%% state space
nfctm = 3; % number of channel to model
A = zeros(nfctm*order);
B = zeros(nfctm*order, nfctm);
C = zeros(nfctm, nfctm*order);
D = zeros(nfctm, nfctm);
pump_state = [];
for i = 1:nfctm
    [a,b,c,d] = ssdata(sys_d);
    A(i*order-order+1:i*order, i*order-order+1:i*order) = a;
    B(i*order-order+1:i*order, i) = b;
    C(i, i*order-order+1:i*order) = c;
    D(i, i) = d;
    for j = 1:order
        pump_state = [pump_state; {['pump_ch' num2str(i) '_k-' num2str(j-1)]}];
    end
    clear j
end
save('pump_sysid_freq.mat','sys','sys_d',...
    'A','B','C','D','Ts','pump_state');
clear i a b c d A B C D


%% bode check fit
close all
figure 
pzmap(sys)
zgrid
grid on

[mag_c,phase_c] = bode(sys,omega);
mag_c = squeeze(mag_c); % not dB
phase_c = squeeze(phase_c);
% phase_c = phase_c - 360; % pade is -ve starts at 360
[mag_d,phase_d] = bode(sys_d,omega);
mag_d = squeeze(mag_d); % not dB
phase_d = squeeze(phase_d);
% phase_d = phase_d - 360; % pade is -ve starts at 360

mag_exp = read_amp./write_amp; % not dB
phase_exp = read_phase - write_phase; % radians


for c = 1:size(data,2)
    figure
    
    subplot(2,1,1)
    semilogx(omega, 20*log10(mag_exp(:,c)),'r+')
    hold on
%     semilogx(omega, 20*log10(mag_c), 'k')
    semilogx(omega, 20*log10(mag_d), 'b')
%     xlabel('Frequency [rad/s]')
    ylabel('Magnitude [dB]')
    grid minor
    title(['Pump Fit (ch' num2str(c) ')'])
    legend('Experiment','Model')
        
    subplot(2,1,2)
    semilogx(omega, phase_exp(:,c)./pi()*180,'r+')
    hold on
%     semilogx(omega, phase_c, 'k')
    semilogx(omega, phase_d, 'b')
    xlabel('Frequency [rad/s]')
    ylabel('Phase [deg]')
    grid minor
%     legend('experiment','continuous model','discrete model')
    
end
clear c


%% compare to time domain data
clear data signal
load('time_domain_data_150-250_step.mat')
% load('time_domain_data_150-250_ramp2s.mat')
% load('time_domain_data_150-250_ramp05s.mat')
% load('time_domain_data_150-250_ramp025s.mat')

% clean data
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
clear i k


figure;
for i = 1:length(data)
    subplot(4,1,i)
% for i = 1:2
%     subplot(2,1,i)
    hold on
    
    grid minor
    t = linspace(min(data(i).out_time),max(data(i).out_time),length(data(i).out_time));
%     y = lsim(sys,data(i).in_value,t);
    yd = lsim(sys_d,data(i).in_value);
    plot(data(i).in_time, data(i).in_value, 'r.-')
    plot(data(i).out_time, data(i).out_value, 'k+')
%     plot(t, y, 'g')
    plot(t, yd, 'b')
    title(['Pump Step Response Ch' num2str(i)])
    xlabel('time[s]')
    ylabel('pressure[mbar]')
%     legend('command','measured','continuous model','discrete model')
    legend('exp (commanded)','exp (measured)','sim (2nd order discrete model)')
    xlim([54 69])
end
clear i y t yd


