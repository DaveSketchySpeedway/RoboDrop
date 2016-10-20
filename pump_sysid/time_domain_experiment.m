clear 
close all
clc
format longEng
set(0, 'DefaulttextInterpreter','none')


% constants
STEP_INTERVAL = 0.25;
STEP_NUMBER = 20;
STEP_MIN = 150;
STEP_MAX = 250;
PUMP_SN = 863;
SAMPLE_PERIOD = 0.1;
CHANNEL_TO_TEST = [1 2 3 4];

%% generate step command (fixed mean)
m = (STEP_MAX + STEP_MIN) / 2;
increment = round((STEP_MAX - STEP_MIN) / 2 / STEP_NUMBER);
signal.time = 0;
signal.value = m;
for i = 1:STEP_NUMBER
    signal.time = [signal.time; max(signal.time)+STEP_INTERVAL];
    signal.value = [signal.value; m + i*increment];
    signal.time = [signal.time; max(signal.time)+STEP_INTERVAL];
    signal.value = [signal.value; m - i*increment];
end
signal.interval = STEP_INTERVAL;
% signal.duration = max(signal.time)+ STEP_INTERVAL;
signal.duration = max(signal.time);
signal.max = max(signal.value);
signal.min = min(signal.value);
signal.mean = m;
clear m increment i

figure; 
plot(signal.time,signal.value,'-o')
title('Step Command')
xlabel('time [s]')
ylabel('pressure [mbar]')
drawnow

%% generate step command (fixed floor)
m = (STEP_MAX + STEP_MIN) / 2;
increment = round((STEP_MAX - STEP_MIN) / STEP_NUMBER);
signal.time = 0;
signal.value = STEP_MIN;
for i = 1:STEP_NUMBER
    signal.time = [signal.time; max(signal.time)+STEP_INTERVAL];
    signal.value = [signal.value; STEP_MIN + i*increment];
    signal.time = [signal.time; max(signal.time)+STEP_INTERVAL];
    signal.value = [signal.value; STEP_MIN];
end
signal.interval = STEP_INTERVAL;
% signal.duration = max(signal.time)+ STEP_INTERVAL;
signal.duration = max(signal.time);
signal.max = max(signal.value);
signal.min = min(signal.value);
signal.mean = m;
clear m increment i

figure; 
plot(signal.time,signal.value,'-o')
title('Step Command')
xlabel('time [s]')
ylabel('pressure [mbar]')
drawnow

%% test 
data = fluigent_run_test(signal,CHANNEL_TO_TEST,PUMP_SN,SAMPLE_PERIOD);
save('time_domain_data.mat','data')

%% plot data

figure;
for i = 1:length(data)
    subplot(4,1,i)
    hold on
    grid minor
%     axis([0,2,0,1000])
    plot(data(i).in_time, data(i).in_value, '-r.')
    plot(data(i).out_time, data(i).out_value, 'b.')
    title(['Channel ' num2str(i) ' command and measure'])
    xlabel('time[s]')
    ylabel('pressure[mbar]')
end





