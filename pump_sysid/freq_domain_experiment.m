clear 
close all
clc
format longEng
set(0, 'DefaulttextInterpreter','none')


% constants
SIN_MEAN = 400;
SIN_AMPLITUDE = 200;
SIN_FREQUENCY = [0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1,...
    1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2,...
    2.25 2.5 2.75 3 3.25 3.5 3.75 4 4.25 4.5];
SIN_DURATION = 10.05; 
PUMP_SN = 863;
SAMPLE_PERIOD = 0.1;
CHANNEL_TO_TEST = [1 2 3 4];

semilogx(SIN_FREQUENCY,SIN_FREQUENCY,'x')
xlim([0.02 20])

%% sinusoidal command 
figure
for f = 1:length(SIN_FREQUENCY)
    signal(f).time = 0:SAMPLE_PERIOD:SIN_DURATION;
    signal(f).value =...
        SIN_AMPLITUDE * sin(2*pi()*SIN_FREQUENCY(f)*signal(f).time) + SIN_MEAN;

    signal(f).frequency = SIN_FREQUENCY(f);
    signal(f).duration = max(signal(f).time);
    signal(f).max = max(signal(f).value);
    signal(f).min = min(signal(f).value);
    signal(f).mean = SIN_MEAN;
    
    subplot(length(SIN_FREQUENCY)/2,2,f)    
    plot(signal(f).time,signal(f).value);
    title([num2str(SIN_FREQUENCY(f)) 'hz']);
    hold on
end
clear f



%% test 

data = [];
for f = 1:length(SIN_FREQUENCY)
    display(['testing at ' num2str(SIN_FREQUENCY(f)) ' hz'])
    raw = fluigent_run_test(signal(f),CHANNEL_TO_TEST,PUMP_SN,SAMPLE_PERIOD);
    data = [data; raw];
    save('freq_domain_data.mat','data')
end
clear raw f
save('freq_domain_data.mat','signal','-append')

%% plot data

for f = 1:length(SIN_FREQUENCY)
    figure;
    for c = 1:length(CHANNEL_TO_TEST)
        subplot(4,1,c)
        hold on
        grid minor
    %     axis([0,2,0,1000])
        plot(data(f,c).in_time, data(f,c).in_value, '-r.')
        plot(data(f,c).out_time, data(f,c).out_value, 'b.')
        title(['Channel ' num2str(c) ' at ' num2str(SIN_FREQUENCY(f)) ' hz'])
        xlabel('time[s]')
        ylabel('pressure[mbar]')
    end
end
clear f c



