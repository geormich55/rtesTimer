N=35999;
error=zeros(N,1);
for i=2:N
error(i)=(abs(A(i))-abs(A(i-1)))-(0.1*10^6);
end

