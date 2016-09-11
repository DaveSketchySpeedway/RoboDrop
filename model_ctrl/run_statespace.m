% numerically compute y and x base on u
% u, x, y: time travel along row



function [x, y] = run_statespace(A,B,C,D,t,u)



n = size(A,1);
m = size(B,2);
p = size(C,1);

x = zeros(n,length(t));
y = zeros(p,length(t));

for k = 1:length(t)
    y(:,k) = C*x(:,k) + D*u(:,k);
    if k < length(t)
        x(:,k+1) = A*x(:,k) + B*u(:,k);
    end
end
