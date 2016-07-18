

%% ATENUATION
clear 
close all
fmin = -1;
fmax = 5;
dbmin = -200;
dbmax = 100;
resolution = 1000;
omega = logspace(fmin,fmax,resolution); % hz
omega = omega * 2 * pi(); % rad/s

load('model_i3_c3_f2_equal_oil.mat'); 
a1 = model.chip.Ac;
b1 = model.chip.Bc;
c1 = model.chip.Cc;
d1 = model.chip.Dc;
s = tf('s');
transfer_functions = d1 + c1*inv(eye(size(a1))*s - a1) * b1;
sys1 = transfer_functions(1,1);
[mag1, phase1] = bode(sys1, omega);
fb1 = interp1(mag1, omega, 0.7);
mag1 = squeeze(mag1);
phase1 = squeeze(phase1);

load('model_i3_c3_f2_equal_h2o'); 
a2 = model.chip.Ac;
b2 = model.chip.Bc;
c2 = model.chip.Cc;
d2 = model.chip.Dc;
transfer_functions = d2 + c2*inv(eye(size(a2))*s - a2) * b2;
sys2 = transfer_functions(1,1);
[mag2, phase2] = bode(sys2, omega);
fb2 = interp1(mag2, omega, 0.7);
mag2 = squeeze(mag2);
phase2 = squeeze(phase2);




figure 
semilogx(omega/2/pi(), 20*log10(mag1), 'r') 
hold on
semilogx(omega/2/pi(), 20*log10(mag2), 'b') 
hold on
line([fb1/2/pi() fb1/2/pi()],[dbmin 20*log10(0.7)], 'Color', 'r')
hold on
line([fb2/2/pi() fb2/2/pi()], [dbmin 20*log10(0.7)], 'Color', 'b')



ylabel('Magnitude dB')
xlabel('Frequency Hz')
title('Chip Frequency Response: Pressure to Displacement')
xlim([10^fmin, 10^fmax])
ylim([dbmin, dbmax])
grid minor
legend('Silicone Oil (50cSt)', 'H2O');



%% POLES AND ZEROS FULL CHIP
clearvars -except model ctrl_c
clc
close all

a = model.chip.Ac;
b = model.chip.Bc;
c = model.chip.Cc;
d = model.chip.Dc;
m = [a, b; c, d];
i = [ones(size(a)), zeros(size(b)); zeros(size(c)), zeros(size(d))];
[v,z] = eig(m, i);
p = eig(a);

%% TRANSMISSION ZEROS SUBPLANT
clearvars -except model ctrl_c
clc
close all

A = ctrl_c(6).A;
B = ctrl_c(6).B;
C = ctrl_c(6).C;
D = ctrl_c(6).D;

pole = eig(A);

sys = tf(ss(A,B,C,D));

trans_zero = [];
for i = 1:size(sys,1)
    for j = 1:size(sys,2)
        [z, p, k] = zpkdata(sys(i,j));
        z = cell2mat(z);
        trans_zero = [trans_zero; z];
%         [num, den] = tfdata(sys(i,j));
%         num = cell2mat(num);
%         den = cell2mat(den);
%         trans_zero = [trans_zero, num];
    end
end
clear i j

%% POLES AND ZEROS SUBPLANT
clearvars -except model ctrl_c
clc
close all

A = ctrl_c(6).A;
B = ctrl_c(6).B;
C = ctrl_c(6).C;
D = ctrl_c(6).D;

pole = eig(A);

% ( i z - m ) = 0  <--> m v = i v z
zero = [];
for j = 1:size(B,2)
%     for k = 1:size(C,1)
        a = A;
        b = B;
        c = C;
        d = D;
        b(:,j) = [];
        d(:,j) = [];
%         c(k,:) = [];
%         d(k,:) = [];
        m = [a, b; c, d];
        i = [ones(size(a)), zeros(size(b)); zeros(size(c)), zeros(size(d))];
        [v,z] = eig(m, i);
        zero = [zero; diag(z)];
%     end
end
clear j k

