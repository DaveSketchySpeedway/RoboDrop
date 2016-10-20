% y = amp * sin(2*pi()t + phase) + m
%   = amp*( sin(wt)*cos(phase) + cos(wt)*sin(phase) ) + mean 
%
% @ y output vector
% @ t time vector
% @ f frequency value in hz
%
% return amp
% return phase in radians
% return mean


function [amp,phase,mean] = least_square_sin(y,t,f)

if max(size(t)) ~= max(size(y))
    display('time and output vector size unequal.')
    return
end

if isrow(y)
    y = y';
end

if isrow(t)
    t = t';
end
    
regression_matrix = [sin(2*pi()*f.*t), cos(2*pi()*f.*t),ones(length(t),1)];
theta = pinv(regression_matrix)*y;

amp = sqrt(theta(1)^2 +theta(2)^2);
phase = atan2(theta(2),theta(1));
if phase < 0
    phase = 2*pi() + phase;
end
mean = theta(3);

end




