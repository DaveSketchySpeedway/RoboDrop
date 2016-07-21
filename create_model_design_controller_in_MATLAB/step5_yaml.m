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



% this script parse the designed controllers into yaml
% MATLAB linear indexing is down a column first, so transpose before stream
% MATLAB is one indiced, hence -1

%% erase redundant controllers
combinations.channel_idx = 0; 
i = 1;
while i <= length(ctrl_c)
    sorted_combination = sort(ctrl_c(i).channel_idx);
    is_duplicated = 0;
    for j = 1:length(combinations)
        if isequal(sorted_combination, combinations(j).channel_idx)
            is_duplicated = 1;
        end
    end
    if is_duplicated == 1
        ctrl_c(i) = [];        
    else
        next = length(combinations) + 1;
        combinations(next).channel_idx = sorted_combination;
        i = i + 1;
    end
end
clearvars -except ctrl_c ctrl_d model



combinations.channel_idx = 0; 
i = 1;
while i <= length(ctrl_d)
    sorted_combination = sort(ctrl_d(i).channel_idx);
    is_duplicated = 0;
    for j = 1:length(combinations)
        if isequal(sorted_combination, combinations(j).channel_idx)
            is_duplicated = 1;
        end
    end
    if is_duplicated == 1
        ctrl_d(i) = [];        
    else
        next = length(combinations) + 1;
        combinations(next).channel_idx = sorted_combination;
        i = i + 1;
    end
end
clearvars -except ctrl_c ctrl_d model
%%

filename = strrep(ctrl_d(1).name, 'model', 'ctrl');
filename = [filename '.yaml'];
file = fopen(filename, 'w');
fprintf(file, '%%YAML:1.0\n');
fprintf(file, 'numCtrl: %d\n', length(ctrl_d));
fprintf(file, 'samplePeriod: %e\n', model.chip.Ts);
fprintf(file, 'numPlantState: %d\n', length(model.chip.state_d));
fprintf(file, 'numPlantInput: %d\n', length(model.chip.input));
fprintf(file, 'numPlantOutput: %d\n', length(model.chip.output));

%%
for i = 1:length(ctrl_d)
% for i = 1:1
    fprintf(file, 'ctrl%d: \n', i-1);
    CTRL = ctrl_d(i);
    fprintf(file, '  uncoUnob: %d\n', CTRL.unco_unob);
    % matrix of decimal notation
    matrixNames = {'outputIdx','stateIdx'};
    for j = 1:length(matrixNames)
        matrixName = matrixNames{j};
        matrix = CTRL.(matrixName)'; % inverse for linear indexing
        [cols, rows] = size(matrix);
        fprintf(file, '  %s: !!opencv-matrix\n', matrixName);
        fprintf(file, '    rows: %d\n', rows);
        fprintf(file, '    cols: %d\n', cols);
        fprintf(file, '    dt: u\n'); % unsigned char
        fprintf(file, '    data: [ ');
        for k = 1:rows*cols
            fprintf(file, '%d', matrix(k)-1 );
            if (k == rows*cols)
                break;
            end
            fprintf(file, ', ');
            if mod(k,cols) == 0
                fprintf(file, '\n            ');
            end
        end
        clear k cols rows matrix
        fprintf(file,' ]\n');
    end
    clear j
    % matrix of exponential notation 
    matrixNames = {'A','B','C','D','K1','K2','H'};
    for j = 1:length(matrixNames)
        matrixName = matrixNames{j};
        matrix = CTRL.(matrixName)'; % inverse for linear indexing
        [cols, rows] = size(matrix);
        fprintf(file, '  %s: !!opencv-matrix\n', matrixName);
        fprintf(file, '    rows: %d\n', rows);
        fprintf(file, '    cols: %d\n', cols);
        fprintf(file, '    dt: d\n'); % double
        fprintf(file, '    data: [ ');
        for k = 1:rows*cols
            fprintf(file, '%.12e', matrix(k));
            if (k == rows*cols)
                break;
            end
            fprintf(file, ', ');
            if mod(k,cols) == 0
                fprintf(file, '\n            ');
            end
        end
        clear k cols rows matrix
        fprintf(file,' ]\n');
    end
    clear j
end
clear i

%%
fclose(file);
clear file ans


