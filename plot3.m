time_without_error=zeros(N,1);
time_without_error(1)=0;
for i=2:N
    time_without_error(i)= time_without_error(i-1)+(0.1*10^6);
end

real_time= time_without_error+error;


figure;
plot([real_time time_without_error]);
ylabel('time(u_sec)');
xlabel('sample_number');
title('rstimer');
legend({'real', 'without_error'})