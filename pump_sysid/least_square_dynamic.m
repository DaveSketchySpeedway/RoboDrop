
function [a,b,v_check,residue,sys,sys_d] = least_square_dynamic(u, v, Ts, order)

regression_matrix = [];
for i = 1:order
    regression_matrix = [regression_matrix, v(order+1-i:end-i)];
end
for i = 1:order+1
    regression_matrix = [regression_matrix, u(order+2-i:end+1-i)];
end
parameter_vector = pinv(regression_matrix) * v(order+1:end);

a = [];
b = [];
for i = 1:order;
    a = [a -parameter_vector(i)];
end
for i = 1:order+1
    b = [b parameter_vector(order + i)];
end

sys_d = tf(b,[1,a],Ts);
sys = d2c(sys_d,'zoh');

v_check = lsim(sys_d,u);
residue = v - v_check;

end