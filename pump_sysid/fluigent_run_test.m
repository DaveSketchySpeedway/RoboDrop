% fluigent_run_test(command,test_channel,serial,sample_period))
%
% @ command is a structure containing input signal to the pump that 
%       will be sampled by the timer
% @ test_channel indicate which channel to be purturbed
% @ serial is pump serial number
% @ sample_period will be divided by num of channels to get timer_period
% return nothing
%
% hard coded to run 4 channels in sequence
% multi pump need multi thread anywyas



function [data] = fluigent_run_test(command,test_channel,serial,sample_period)
clear MUTATE CONSTANT DATA QUEUE
global CONSTANT MUTATE DATA QUEUE

%% create timer
CONSTANT.color = 'cygm';
CONSTANT.channel = [1,2,3,4];
CONSTANT.test_channel = test_channel;
CONSTANT.serial = serial;
CONSTANT.command = command;

timer_period = sample_period / length(CONSTANT.channel);
timer_period = timer_period + mod(timer_period, 0.001);

CONSTANT.timer1 = timer('ExecutionMode','fixedRate',...
    'Period',timer_period,...
    'TimerFcn',{@timer_update_fcn},...
    'StartDelay',0,...
    'StartFcn', {@timer_start_fcn}, ...
    'StopFcn', {@timer_stop_fcn},...
    'BusyMode','drop');
%     'BusyMode','error',...
%     'ErrorFcn',{@timer_error_fcn});

queue_length = 20;
for i = 1:length(CONSTANT.channel)
    DATA(i).in_value = [];
    DATA(i).in_time = [];
    DATA(i).out_value =[];
    DATA(i).out_time = [];
    QUEUE(i).in_value = zeros(queue_length,1);
    QUEUE(i).in_time = zeros(queue_length,1);
    QUEUE(i).out_value = zeros(queue_length,1);
    QUEUE(i).out_time = zeros(queue_length,1);
end

%% initialize pump
CONSTANT.handle = mfcs_init(CONSTANT.serial);
CONSTANT.init_flag = 1;

status = mfcs_get_status(CONSTANT.handle);
switch status 
    case 0
        msg = ['pump sn' num2str(CONSTANT.serial)...
            ' need manaul reset'];
        error(msg)
    case 1
        display(['pump sn' num2str(CONSTANT.serial)...
            ' initialized and is ready'])
end

%% start test

% figure
MUTATE.last_update_time = 0;
MUTATE.next_sequence = 1;
MUTATE.pump_last_read_time = zeros(1,length(CONSTANT.channel));

if strcmp(get(CONSTANT.timer1, 'Running'), 'off')
    % record start times for future reference
    CONSTANT.timer_start_tic = tic;
    [read_value,chrono] = mfcs_read_chan(CONSTANT.handle,1);
    CONSTANT.pump_start_time = double(chrono)*0.025; % 1 chrono is 25ms
    start(CONSTANT.timer1);
end

%% wait for test
while strcmp(get(CONSTANT.timer1, 'Running'), 'on')
end

%% save data
data = DATA;

%% delete timer
delete(timerfindall)






function timer_start_fcn(hObject,eventdata)
% not using timer start function because it eats into the first update fcn


function timer_stop_fcn(hObject,eventdata)
global CONSTANT MUTATE  

%% timer statistics
[r,chrono] = mfcs_read_chan(CONSTANT.handle,1);
pump_duration = double(chrono)*0.025 - CONSTANT.pump_start_time;
num_of_tasks = ceil(MUTATE.last_update_time / get(CONSTANT.timer1,'Period'));
num_of_execution = get(hObject, 'TasksExecuted');
avg_timer_period = get(hObject, 'AveragePeriod');
display(['executed ' num2str(num_of_execution)...
    ' out of ' num2str(num_of_tasks) ' tasks'])
display(['average timer period is ' num2str(avg_timer_period)])
display(['test duratioin is ' num2str(pump_duration) ' according to pump'])

%% set zero and close CONSTANT
if CONSTANT.init_flag == 1
    mfcs_init(CONSTANT.serial);
    mfcs_close(CONSTANT.handle);
   CONSTANT.init_flag = 0;
    display(['pump sn' num2str(CONSTANT.serial) ' zeroed and closed'])
else
    display(['pump sn' num2str(CONSTANT.serial) ' already closed'])
end



function timer_error_fcn(hObject,eventdata)
display('TIMER STOPPED DUE TO MISSED UPDATE (timer period too short)')



function timer_update_fcn(hObject,eventdata)
global CONSTANT MUTATE DATA QUEUE
MUTATE.last_update_time = toc(CONSTANT.timer_start_tic);
% tic

%% increment sequence (timer throw error for any missed update)
seq = MUTATE.next_sequence;
if seq < length(CONSTANT.channel)
    MUTATE.next_sequence = seq + 1;
elseif seq == length(CONSTANT.channel)
    MUTATE.next_sequence = 1;
else
    MUTATE.next_sequence = 1;
end
% toc

%% find out what to write to CONSTANT
include = find(CONSTANT.test_channel == CONSTANT.channel(seq),1);
if isempty(include)
    w = CONSTANT.command.mean;
else
    % step
%     cmd_idx = find(CONSTANT.command.time < MUTATE.last_update_time, 1, 'last');
%     w = CONSTANT.command.value(cmd_idx);
    % ramp
    w = interp1(CONSTANT.command.time,CONSTANT.command.value,MUTATE.last_update_time);
end
% toc

%% write and read
mfcs_set_auto(CONSTANT.handle,w,CONSTANT.channel(seq));
wt = toc(CONSTANT.timer_start_tic);
% toc
[r,chrono] = mfcs_read_chan(CONSTANT.handle,CONSTANT.channel(seq));
rt = double(chrono)*0.025 - CONSTANT.pump_start_time;
% toc

%% check bad read
if rt == MUTATE.pump_last_read_time(seq)
    display('bad read')
end
MUTATE.pump_last_read_time(seq) = rt;

%% store
DATA(CONSTANT.channel(seq)).in_value = [DATA(CONSTANT.channel(seq)).in_value; w];
DATA(CONSTANT.channel(seq)).in_time = [DATA(CONSTANT.channel(seq)).in_time; wt];
DATA(CONSTANT.channel(seq)).out_value = [DATA(CONSTANT.channel(seq)).out_value; r];
DATA(CONSTANT.channel(seq)).out_time = [DATA(CONSTANT.channel(seq)).out_time; rt];
% toc

%% queue
QUEUE(CONSTANT.channel(seq)).in_value =...
    [QUEUE(CONSTANT.channel(seq)).in_value(2:end); w];
QUEUE(CONSTANT.channel(seq)).in_time =...
    [QUEUE(CONSTANT.channel(seq)).in_time(2:end); wt];
QUEUE(CONSTANT.channel(seq)).out_value =...
    [QUEUE(CONSTANT.channel(seq)).out_value(2:end); r];
QUEUE(CONSTANT.channel(seq)).out_time =...
    [QUEUE(CONSTANT.channel(seq)).out_time(2:end); rt];
% toc

%% plot (Performance Killer)
% if seq == length(CONSTANT.channel)
%     tic
%     for i = 1:length(CONSTANT.channel)
%         plot(QUEUE(i).out_time,QUEUE(i).out_value,'.','color',CONSTANT.color(i))
%         hold on
%     end
%     hold off
%     drawnow
%     toc
% end


%% stop timer
if MUTATE.last_update_time >= CONSTANT.command.duration
    if strcmp(get(CONSTANT.timer1, 'Running'), 'on')
        stop(CONSTANT.timer1)
    end
end
% toc








