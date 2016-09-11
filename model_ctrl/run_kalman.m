% perform kalman prediction on existing data
% u and y: travel in time along row


function [state_estimation, state_prediction, output_prediction,...
    estimation_covariance, prediction_covariance, kalman] =...
    run_kalman(A,B,W,C,Rw,Rv,t,u,y)


n = size(A,1);
m = size(B,2);
p = size(C,1);



initial_est_cov = 1e3;
estimation_covariance = initial_est_cov .* ones(n,n,length(t));
prediction_covariance = zeros(n,n,length(t));
kalman = zeros(n,p,length(t));
state_prediction = zeros(n,length(t));
output_prediction = zeros(p,length(t));
error = zeros(p,length(t));
state_estimation = zeros(n,length(t));



for k = 2:length(t)
   
    prediction_covariance(:,:,k) =...
        A*estimation_covariance(:,:,k-1)*A' + W*Rw*W';

    kalman(:,:,k) =...
        prediction_covariance(:,:,k)*C'/...
        (C*prediction_covariance(:,:,k)*C' + Rv);

    estimation_covariance(:,:,k) =...
        (eye(n,n) - kalman(:,:,k)*C)*prediction_covariance(:,:,k);

    state_prediction(:,k) = A*state_estimation(:,k-1) + B*u(:,k-1);
    output_prediction(:,k) = C*state_prediction(:,k);
    error(:,k) = y(:,k) - output_prediction(:,k);
    state_estimation(:,k) = state_prediction(:,k) + kalman(:,:,k)*error(:,k);


end
clear k