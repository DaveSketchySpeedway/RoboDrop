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


% this script:
% reduce plant model base on degrees of freedom 
% construct integral state feed back augmented state space
% check controllibility then lqr feedback gains
% check observability than lqr observer gains
% construct close loop state space


clearvars -except model
close all
clc

MAX_DOF = false;
% MAX_DOF = true;
PLANT = model.chip;
% PLANT = model.combo;
TOL = 1e-12;
ISFB_R = 1;
ISFB_Q_POSITION = 1;
ISFB_Q_VELOCITY = 0.1;
ISFB_Q_PRESSURE = 1;
ISFB_Q_INTEGRAL = 10;
OBSR_R = 1;
OBSR_Q_POS_ERROR = 0.1;
OBSR_Q_VEL_ERROR = 1;
OBSR_Q_PRES_ERROR = 1;

%% REDUCE PLANT
num_channel = length(PLANT.output);
num_inlet = length(PLANT.input);
num_dof = num_inlet - 1;

% channels to keep
allset = 1:num_channel;
subset = nchoosek(allset, num_dof);
if (MAX_DOF)
    channel_keep = subset;
else
    l = 1;
    for i = 1:size(subset,1);
        for j = 1:size(subset,2);
            subsubset = nchoosek(subset(i,:), j);
            for k = 1:size(subsubset,1);
                channel_keep(l,:) = [subsubset(k,:),...
                    zeros(1,size(subset,2) - size(subsubset,2))];
                l = l+1;
            end
            clear subsubset
        end
    end
end
clear subset
clear i j k l

% channels to delete
channel_delete = zeros(size(channel_keep,1), num_channel-1);
for i = 1:size(channel_keep,1)
    k = 1;
    for j = allset
        found = find(channel_keep(i,:) == j);
        if (isempty(found))
            channel_delete(i,k) = j;
            k = k + 1;
        end
    end
end
clear i j k found
clear num_* 


%% CONTINUOUS CONTROLLER DESIGN
for i = 1:size(channel_keep,1)   
    ts = PLANT.Ts;
    output_idx = channel_keep(i,:);
    output_idx = output_idx(output_idx ~= 0);
    output = PLANT.output(output_idx);
    state_idx = [output_idx, length(allset)+1:size(PLANT.Ac,1)];
    state = PLANT.state_c(state_idx);
    state_aug = [state; output];
        
    % reduction
    a = PLANT.Ac;
    b = PLANT.Bc;
    c = PLANT.Cc;
    d = PLANT.Dc;
    for j = channel_delete(i,:)
        if (j~=0)
            a(j,:) = nan;
            b(j,:) = nan;
            c(j,:) = nan;
            d(j,:) = nan;
            a(:,j) = nan;
            c(:,j) = nan;
        end
    end
    clear j
    a(:,all(isnan(a),1)) = []; % delete entire col that is nan
    a(all(isnan(a),2),:) = []; % delete entire row that is nan
    b(:,all(isnan(b),1)) = []; 
    b(all(isnan(b),2),:) = []; 
    c(:,all(isnan(c),1)) = []; 
    c(all(isnan(c),2),:) = []; 
    d(:,all(isnan(d),1)) = []; 
    d(all(isnan(d),2),:) = []; 
    n = size(a,1);
    m = size(b,2);
    p = size(c,1);
    
    % augmentation
    ag = [a zeros(n,p); c zeros(p,p)];
    bg = [b; d];
    cg = [c zeros(p,p)];
    dg = d;
    br = [zeros(n,p); -eye(p,p)];
    ng = size(ag,1);
    mg = size(bg,2);
    pg = size(cg,1);
    
    % controllability
    uncontrollable = 0;
    pole = eig(ag);
    for j = 1:length(pole)
        comat_rank(j,:) = rank([ag - pole(j)*eye(size(ag)), bg]);
        if comat_rank(j,:) < size(ag,1);
            uncontrollable = uncontrollable + 1;
        end
    end
    clear j pole 
    
    % observability
    unob_unco = 0;
    pole = eig(a);
    for j = 1:length(pole)
        obmat_rank(j,:) = rank([c; a - pole(j)*eye(size(a))]);
        if obmat_rank(j,:) < size(a,1);
            unob_unco = unob_unco + 1;
        end
    end
    clear j pole

    % LQR integral state feed back
    qg = [];
    rg = [];
    kg = [];
    k1 = [];
    k2 = [];
    if (uncontrollable == 0 && MAX_DOF == 1) || (MAX_DOF == 0)
        try
            qg = eye(ng,ng);
            rg = eye(mg,mg)*ISFB_R;
            qg(1:p, 1:p) = eye(p,p)*ISFB_Q_POSITION;
            qg(n+1:ng, n+1:ng) = eye(p,p)*ISFB_Q_INTEGRAL;
            for j = 1:ng
                if ~isempty(strfind(cell2mat(state_aug(j)), 'Il_'))
                    qg(j,j) = ISFB_Q_VELOCITY;
                end
                if ~isempty(strfind(cell2mat(state_aug(j)), 'Uc_'))
                    qg(j,j) = ISFB_Q_PRESSURE;
                end
            end   
            clear j
            [kg, sol, pole] = lqr(ag, bg, qg, rg);
            k1 = kg(1:m, 1:n);
            k2 = kg(1:m, n+1:n+p);
            clear sol pole   
        end
    end
    
    % LQR observer 
    q = [];
    r = [];
    h = [];
    if (unob_unco == 0 && MAX_DOF == 1) || (MAX_DOF == 0)
        try 
            q = eye(n,n);
            r = eye(p,p)*OBSR_R;
            q(1:p, 1:p) = eye(p,p)*OBSR_Q_POS_ERROR;
            for j = 1:n
                if ~isempty(strfind(cell2mat(state(j)), 'Il_'))
                    q(j,j) = OBSR_Q_VEL_ERROR;
                end
                if ~isempty(strfind(cell2mat(state(j)), 'UC_'))
                    q(j,j) = OBSR_Q_PRES_ERROR;
                end
            end    
            clear j
            [h, sol, pole] = lqr(a', c', q, r);
            h = h';
            clear sol pole        
        end
    end
    
    % closed loop
    acl = [];
    bcl = [];
    ccl = [];
    dcl = [];
    state_cl = [];
    if (~isempty(kg) && ~isempty(h))
        acl = [ag-bg*kg, [b*k1; d*k1];...
            zeros(n,n+p), a-h*c];
        bcl = [br; zeros(n,p)];
        ccl = [cg-dg*kg, d*k1];
        dcl = zeros(p,p);
        state_cl = [state_aug; state];
    end

    % controller 
    ctrl_c(i).Ts = ts;
    ctrl_c(i).name = model.name;
    ctrl_c(i).channel_idx = output_idx;
    ctrl_c(i).input = PLANT.input;
    ctrl_c(i).output = output;
    ctrl_c(i).state = state;
    ctrl_c(i).unobservable = unob_unco;
    ctrl_c(i).Q = q;
    ctrl_c(i).R = r;
    ctrl_c(i).uncontrollable = uncontrollable;
    ctrl_c(i).Qg = qg;
    ctrl_c(i).Rg = rg;
    ctrl_c(i).state_cl = state_cl;  % closed loop
    ctrl_c(i).Acl = acl; 
    ctrl_c(i).Bcl = bcl;
    ctrl_c(i).Ccl = ccl;
    ctrl_c(i).Dcl = dcl;
    ctrl_c(i).state_aug = state_aug; % augmented
    ctrl_c(i).Ag = ag; 
    ctrl_c(i).Bg = bg;
    ctrl_c(i).Cg = cg;
    ctrl_c(i).Dg = dg;
    ctrl_c(i).Br = br;
    ctrl_c(i).stateIdx = state_idx; % reduced
    ctrl_c(i).outputIdx = output_idx;
    ctrl_c(i).n = n;
    ctrl_c(i).m = m;
    ctrl_c(i).p = p;
    ctrl_c(i).A = a; 
    ctrl_c(i).B = b;
    ctrl_c(i).C = c;
    ctrl_c(i).D = d;
    ctrl_c(i).K1 = k1;
    ctrl_c(i).K2 = k2;
    ctrl_c(i).H = h;  
    
    clear input output* state* ts
    clear uncontrollable kg k1 k2 qg rg
    clear unobservable h q r
    clear a b c d n m p
    clear ag bg cg dg br ng mg pg
    clear acl bcl ccl dcl
    clear comat_rank obmat_rank
end
clear i


%% DISCRETE CONTROLLER DESIGN
for i = 1:size(channel_keep,1)   
    ts = PLANT.Ts;
    output_idx = channel_keep(i,:);
    output_idx = output_idx(output_idx ~= 0);
    output = PLANT.output(output_idx);
    state_idx = [output_idx, length(allset)+1:size(PLANT.Ad,1)];
    state = PLANT.state_d(state_idx);
    state_aug = [state; output];
    
        
    % reduction
    a = PLANT.Ad;
    b = PLANT.Bd;
    c = PLANT.Cd;
    d = PLANT.Dd;
    for j = channel_delete(i,:)
        if (j~=0)
            a(j,:) = nan;
            b(j,:) = nan;
            c(j,:) = nan;
            d(j,:) = nan;
            a(:,j) = nan;
            c(:,j) = nan;
        end
    end
    clear j
    a(:,all(isnan(a),1)) = []; % delete entire col that is nan
    a(all(isnan(a),2),:) = []; % delete entire row that is nan
    b(:,all(isnan(b),1)) = []; 
    b(all(isnan(b),2),:) = []; 
    c(:,all(isnan(c),1)) = []; 
    c(all(isnan(c),2),:) = []; 
    d(:,all(isnan(d),1)) = []; 
    d(all(isnan(d),2),:) = []; 
    n = size(a,1);
    m = size(b,2);
    p = size(c,1);
    
    % augmentation
    ag = [a zeros(n,p); c*ts eye(p,p)];
    bg = [b; ts*d];
    cg = [c zeros(p,p)];
    dg = d;
    br = [zeros(n,p); -ts*eye(p,p)];
    ng = size(ag,1);
    mg = size(bg,2);
    pg = size(cg,1);
    
    % controllability
%     uncontrollable = 0;
%     pole = eig(ag);
%     k = rand(mg, pg);
%     eig_abkc = eig(ag + bg*k*cg);
%     for j = 1:length(pole)
%         for l = 1:length(eig_abkc)
%             if abs(pole(j)-eig_abkc(l)) <= ...
%                     TOL*max(abs([pole(j); eig_abkc(l)]))
%                 uncontrollable = uncontrollable + 1;
%             end
%         end
%     end
%     clear j l pole k eig_abkc

    
    % observability
    unob_unco = 0;
    pole = eig(a);
    k = rand(m,p);
    eig_abkc = eig(a + b*k*c);
    for j = 1:length(pole)
        for l = 1:length(eig_abkc)
            if abs(pole(j)-eig_abkc(l)) <= ...
                    TOL*max(abs([pole(j); eig_abkc(l)]))
                unob_unco = unob_unco + 1;
            end
        end
    end
    clear j l pole k eig_abkc

    % LQR integral state feed back
    qg = [];
    rg = [];
    kg = [];
    k1 = [];
    k2 = [];
    if (unob_unco == 0 && MAX_DOF == 1) || (MAX_DOF == 0)
        try
            qg = eye(ng,ng);
            rg = eye(mg,mg)*ISFB_R;
            qg(1:p, 1:p) = eye(p,p)*ISFB_Q_POSITION;
            qg(n+1:ng, n+1:ng) = eye(p,p)*ISFB_Q_INTEGRAL;
            for j = 1:ng
                if ~isempty(strfind(cell2mat(state_aug(j)), 'Il_'))
                    qg(j,j) = ISFB_Q_VELOCITY;
                end
                if ~isempty(strfind(cell2mat(state_aug(j)), 'Uc_'))
                    qg(j,j) = ISFB_Q_PRESSURE;
                end
            end   
            clear j
            [kg, sol, pole] = dlqr(ag, bg, qg, rg);
            k1 = kg(1:m, 1:n);
            k2 = kg(1:m, n+1:n+p);
            clear sol pole   
        end
    end
    
    % LQR observer 
    q = [];
    r = [];
    h = [];
    if (unob_unco == 0 && MAX_DOF == 1) || (MAX_DOF == 0)
        try 
            q = eye(n,n);
            r = eye(p,p)*OBSR_R;
            q(1:p, 1:p) = eye(p,p)*OBSR_Q_POS_ERROR;
            for j = 1:n
                if ~isempty(strfind(cell2mat(state(j)), 'Il_'))
                    q(j,j) = OBSR_Q_VEL_ERROR;
                end
                if ~isempty(strfind(cell2mat(state(j)), 'UC_'))
                    q(j,j) = OBSR_Q_PRES_ERROR;
                end
            end    
            clear j
            [h, sol, pole] = dlqr(a', c', q, r);
            h = h';
            clear sol pole        
        end
    end
    
    % closed loop
    acl = [];
    bcl = [];
    ccl = [];
    dcl = [];
    state_cl = [];
    if (~isempty(kg) && ~isempty(h))
        acl = [ag-bg*kg, [b*k1; ts*d*k1];...
            zeros(n,n+p), a-h*c];
        bcl = [br; zeros(n,p)];
        ccl = [cg-dg*kg, d*k1];
        dcl = zeros(p,p);
        state_cl = [state_aug; state];
    end

    % controller 
    ctrl_d(i).Ts = ts;
    ctrl_d(i).name = model.name;
    ctrl_d(i).channel_idx = output_idx;
    ctrl_d(i).input = PLANT.input;
    ctrl_d(i).output = output;
    ctrl_d(i).state = state;
%     ctrl_d(i).unobservable = unobservable;
    ctrl_d(i).unco_unob = unob_unco;
    ctrl_d(i).Q = q;
    ctrl_d(i).R = r;
%     ctrl_d(i).uncontrollable = uncontrollable;
    ctrl_d(i).Qg = qg;
    ctrl_d(i).Rg = rg;
    ctrl_d(i).state_cl = state_cl;  % closed loop
    ctrl_d(i).Acl = acl; 
    ctrl_d(i).Bcl = bcl;
    ctrl_d(i).Ccl = ccl;
    ctrl_d(i).Dcl = dcl;
    ctrl_d(i).state_aug = state_aug;  % augmented
    ctrl_d(i).Ag = ag;
    ctrl_d(i).Bg = bg;
    ctrl_d(i).Cg = cg;
    ctrl_d(i).Dg = dg;
    ctrl_d(i).Br = br;
    ctrl_d(i).stateIdx = state_idx; % reduced
    ctrl_d(i).outputIdx = output_idx;
    ctrl_d(i).n = n;
    ctrl_d(i).m = m;
    ctrl_d(i).p = p;
    ctrl_d(i).A = a; 
    ctrl_d(i).B = b;
    ctrl_d(i).C = c;
    ctrl_d(i).D = d;
    ctrl_d(i).K1 = k1;
    ctrl_d(i).K2 = k2;
    ctrl_d(i).H = h; 
 
    clear input output* state* ts
    clear uncontrollable kg k1 k2 qg rg
    clear unobservable h q r unob_unco
    clear a b c d n m p
    clear ag bg cg dg br ng mg pg
    clear acl bcl ccl dcl
    clear comat_rank obmat_rank
end
clear i

%% CLEAN UP
clear MAX_DOF PLANT
clear allset channel_delete channel_keep 
clear TOL ISFB* OBSR*
