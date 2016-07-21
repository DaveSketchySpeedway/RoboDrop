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


% this script build state space model for any microfluidics network
% 1) load pump transfer functions, define simulink file name
% 2) setup template for fluid properties
% 3) setup template for container properties
% 4) setup template for chip dimensions
% 5) calculate parameters for each model elements
% 6) assign parameters into simulink model, extract chip statespace
% 7) convert chip statespace output from current to charge
% 8) construct pump statespace 
% 9) combine chip and pump

close all
clc
clear 

TS = 0.1; % sampling period for discretization

load('pump_fit_tf_avg_freq.mat')
% load('pump_fit_tf_avg_time_step.mat')

% MODEL = 'model_i3_c3_f2_valid'; 
% MODEL = 'model_i3_c3_f2_equal_oil'; 
% MODEL = 'model_i3_c3_f2_equal_h2o'; 
% MODEL = 'model_i3_c3_f2_50';
% MODEL = 'model_i4_c4_f3_50';
MODEL = 'model_i4_c5_f3_50a';
% MODEL = 'model_i4_c5_f3_50b';
% MODEL = 'model_i4_c8_f3_50';
% MODEL = 'model_i5_c6_f4_50';
% MODEL = 'model_i5_c7_f4_50a';
% MODEL = 'model_i5_c7_f4_50b';
% MODEL = 'model_i5_c7_f4_100a';
% MODEL = 'model_i5_c7_f4_100b';


MANUAL_SETUP = false;

if (~MANUAL_SETUP)
    load([MODEL '.mat']);
end
%% INITIALIZE FLUID PROPERTIES
if (MANUAL_SETUP)
    % dynamic viscosity Ns/m2 or kg/m/s
    % density kg/m3
    % adiabatic bulk modulus Pa

    % water
    fluid(1).name = 'water';
    fluid(1).viscosity_kg_ms = 0.001;
    fluid(1).density_kg_m3 = 1000;
    fluid(1).bulk_modulus_pa = 2.2e9;

    % silicon oil 50cSt
    fluid(2).name = 'oil_50cSt';
    fluid(2).viscosity_kg_ms = 0.04815;
    fluid(2).density_kg_m3 = 963;
    fluid(2).bulk_modulus_pa = 1.23e9;
end

%% INITIALIZE CONTAINER PROPERTIES
if (MANUAL_SETUP)
    % young modulus Pa
    % wall cross section area mm2

    % big tubing
    container(1).name = 'PFA_1514';
    container(1).young_modulus_pa = 480e6;
    container(1).substrate_xarea_mm2 = 1.52;

    % small tubing
    container(2).name = 'PFA_1902';
    container(2).young_modulus_pa = 480e6;
    container(2).substrate_xarea_mm2 = 1.93;

    % chip
    container(3).name = 'PDMS';
    container(3).young_modulus_pa = 2e6;
    container(3).substrate_xarea_mm2 = 100;
end

%% INITIALIZE DIMENSIONS
if (MANUAL_SETUP)
    % length, radius in mm
    % height, width in um

    dimension(1).name = 'tube1_water';
    dimension(1).f_idx = 1;
    dimension(1).c_idx = 1;
    dimension(1).length_mm = 490;
    dimension(1).radius_mm = 0.127;

    dimension(2).name = 'tube2_oil';
    dimension(2).f_idx = 2;
    dimension(2).c_idx = 2;
    dimension(2).length_mm = 490;
    dimension(2).radius_mm = 0.381;

    dimension(3).name = 'tube3_oil';
    dimension(3).f_idx = 2;
    dimension(3).c_idx = 2;
    dimension(3).length_mm = 490;
    dimension(3).radius_mm = 0.381;

    dimension(4).name = 'ch1_water';
    dimension(4).f_idx = 1;
    dimension(4).c_idx = 3;
    dimension(4).length_mm = 20;
    dimension(4).width_um = 50;
    dimension(4).height_um = 50;

    dimension(5).name = 'ch2_oil';
    dimension(5).f_idx = 2;
    dimension(5).c_idx = 3;
    dimension(5).length_mm = 12;
    dimension(5).width_um = 50;
    dimension(5).height_um = 50;

    dimension(6).name = 'ch3_oil';
    dimension(6).f_idx = 2;
    dimension(6).c_idx = 3;
    dimension(6).length_mm = 7;
    dimension(6).width_um = 50;
    dimension(6).height_um = 50;
end

%% CALCULATE ELEMENT PROPERTIES
if (MANUAL_SETUP)
for i = 1:length(dimension)
    % calculation in SI units
    element(i).name = dimension(i).name;
    element(i).fluid = fluid(dimension(i).f_idx).name;
    element(i).container = container(dimension(i).c_idx).name;
    element(i).length = dimension(i).length_mm * 1e-3;
    element(i).radius = dimension(i).radius_mm * 1e-3;
    element(i).height = dimension(i).height_um * 1e-6;
    element(i).width = dimension(i).width_um * 1e-6;
    if (isempty(dimension(i).radius_mm))
        element(i).xsect_area = element(i).width * element(i).height;
        element(i).hydraulic_diameter = 2 * element(i).height * element(i).width / ...
            (element(i).height + element(i).width);
    else
        element(i).xsect_area = element(i).radius^2 * pi();
        element(i).hydraulic_diameter = 2 * element(i).radius;
    end
    element(i).substrate_stiffness = container(dimension(i).c_idx).substrate_xarea_mm2 * 1e-6 *...
        container(dimension(i).c_idx).young_modulus_pa / element(i).length;
    element(i).viscosity = fluid(dimension(i).f_idx).viscosity_kg_ms;
    element(i).density = fluid(dimension(i).f_idx).density_kg_m3;
    element(i).bulk_modulus = fluid(dimension(i).f_idx).bulk_modulus_pa;
    
    % RLC in SI units
    element(i).resistance = 32 * element(i).viscosity * element(i).length / ...
        element(i).hydraulic_diameter^2;
    element(i).inductance = element(i).density * element(i).length;
    element(i).capacitance = element(i).xsect_area / element(i).substrate_stiffness + ...
        element(i).length / element(i).bulk_modulus;
        
    % RLC um mbar
    element(i).R = element(i).resistance / 100 / 1e6;
    element(i).L = element(i).inductance / 100 / 1e6;
    element(i).C = element(i).capacitance * 100 * 1e6;
end
clear i

end
%% ASSIGN PARAMETER, EXTRACT SS


open(MODEL);
for i = 1:length(element)
    set_param([MODEL '/' element(i).name '/fluid_a'],...
        'Resistance',num2str(element(i).R));
    set_param([MODEL '/' element(i).name '/fluid_a'],...
        'Inductance',num2str(element(i).L));
    set_param([MODEL '/' element(i).name '/fluid_c'],...
        'Capacitance',num2str(element(i).C));    
end
clear i
sps = power_analyze(MODEL,'structure');
save_system(MODEL);
close_system(MODEL);


%% VELOCITY TO POSITION (CURRENT TO CHARGE)

% inputs outputs
n = length(sps.states);
m = length(sps.inputs);
p = length(sps.outputs);
model.chip.output = [];
for i = 1:p
    name = cell2mat(sps.outputs(i));
    a = strfind(name, 'I_') + 2;
%     b = strfind(name, '/current');
%     channel_name = name(a:b);
    channel_name = name(a:end);
    model.chip.output = [model.chip.output; {['Q_' channel_name]}];
    clear a b name channel_name
end
clear i
model.chip.input = sps.inputs;


% continuous
model.chip.Ac = [sps.C; sps.A];
model.chip.Ac = [zeros(p + n, p), model.chip.Ac];
model.chip.Bc = [sps.D; sps.B];
model.chip.Cc = [eye(p, p), zeros(p, n)];
model.chip.Dc = zeros(p, m);
model.chip.state_c = [model.chip.output; sps.states];


% discrete 
[a,b,c,d] = ssdata(c2d(ss(sps.A,sps.B,sps.C,sps.D), TS, 'zoh'));
% a = sps.Adiscrete;
% b = sps.Bdiscrete;
% c = sps.Cdiscrete;
% d = sps.Ddiscrete;
n = size(a,1);
m = size(b,2);
p = size(c,1);
model.chip.Ad = [eye(p,p) c*TS; zeros(n,p), a];
model.chip.Bd = [d*TS; b];
model.chip.Cd = [eye(p,p) zeros(p,n)];
model.chip.Dd = zeros(p,m);
model.chip.Ts = TS;
model.chip.state_d = [model.chip.output; sps.states];  

% [a,b,c,d] = ssdata(c2d(ss(...
%     model.chip.Ac,model.chip.Bc,model.chip.Cc,model.chip.Dc), TS, 'foh'));
% model.chip.Ad = a;
% model.chip.Bd = b;
% model.chip.Cd = c;
% model.chip.Dd = d;
% model.chip.Ts = TS;
% model.chip.state_d = [model.chip.output; sps.states];  

clear a b c d n m p
clear sps 


%% PUMP STATESPACE

% continuous
n = length(model.chip.state_c);
m = length(model.chip.input);
p = length(model.chip.output);
order = length(sys.den{1})-1;
model.pump.Ac = zeros(m*order);
model.pump.Bc = zeros(m*order, m);
model.pump.Cc = zeros(m, m*order);
model.pump.Dc = zeros(m, m);
model.pump.state_c = [];
for i = 1:m
    [a,b,c,d] = ssdata(ss(sys)); % replace with tf2ss maybe
    model.pump.Ac(i*order-order+1:i*order, i*order-order+1:i*order) = a;
    model.pump.Bc(i*order-order+1:i*order, i) = b;
    model.pump.Cc(i, i*order-order+1:i*order) = c;
    model.pump.Dc(i, i) = d;
    clear a b c d 
    for j = 1:order
        channel_name = model.chip.input{i};
        model.pump.state_c = [model.pump.state_c;...
            {['pump_k-' num2str(j-1) '_' channel_name(3:end) ]}];
    end
    clear j channel_name
end
clear i 
model.pump.sys = sys;

% discrete
n = length(model.chip.state_d);
m = length(model.chip.input);
p = length(model.chip.output);
order = length(sys_d.den{1})-1;
model.pump.Ad = zeros(m*order);
model.pump.Bd = zeros(m*order, m);
model.pump.Cd = zeros(m, m*order);
model.pump.Dd = zeros(m, m);
model.pump.state_d = [];
model.pump.Ts = TS;
for i = 1:m
    [a,b,c,d] = ssdata(ss(sys_d));
    model.pump.Ad(i*order-order+1:i*order, i*order-order+1:i*order) = a;
    model.pump.Bd(i*order-order+1:i*order, i) = b;
    model.pump.Cd(i, i*order-order+1:i*order) = c;
    model.pump.Dd(i, i) = d;
    clear a b c d 
        for j = 1:order
        channel_name = model.chip.input{i};
        model.pump.state_d = [model.pump.state_d;...
            {['pump_k-' num2str(j-1) '_' channel_name(3:end) ]}];
    end
    clear j channel_name
end
clear i 
model.pump.sys_d = sys_d;

clear sys sys_d n m p order






%% COMBINE

% dicrete
model.combo.Ts = TS;
np = size(model.pump.Ad,1);
mp = size(model.pump.Bd,2);
pp = size(model.pump.Cd,1);

nc = size(model.chip.Ad,1);
mc = size(model.chip.Bd,2);
pc = size(model.chip.Cd,1);

model.combo.Ad = [model.chip.Ad, model.chip.Bd*model.pump.Cd;...
    zeros(np,nc), model.pump.Ad];
model.combo.Bd = [model.chip.Bd*model.pump.Dd;...
    model.pump.Bd];
model.combo.Cd = [model.chip.Cd, model.chip.Dd*model.pump.Cd];
model.combo.Dd = [model.chip.Dd*model.pump.Dd];
model.combo.state_d = [model.chip.state_c; model.pump.state_d];

% continuous
np = size(model.pump.Ac,1);
mp = size(model.pump.Bc,2);
pp = size(model.pump.Cc,1);

nc = size(model.chip.Ac,1);
mc = size(model.chip.Bc,2);
pc = size(model.chip.Cc,1);

model.combo.Ac = [model.chip.Ac, model.chip.Bc*model.pump.Cc;...
    zeros(np,nc), model.pump.Ac];
model.combo.Bc = [model.chip.Bc*model.pump.Dc;...
    model.pump.Bc];
model.combo.Cc = [model.chip.Cc, model.chip.Dc*model.pump.Cc];
model.combo.Dc = [model.chip.Dc*model.pump.Dc];
model.combo.state_c = [model.chip.state_d; model.pump.state_c];

model.combo.input = model.chip.input;
model.combo.output = model.chip.output;

clear np mp pp nc mc pc ap bp cp dp

model.name = MODEL;
save(MODEL,'fluid','container','dimension','element','model');
clear fluid container dimension element MODEL TS 

