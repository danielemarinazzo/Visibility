function [NN k k_in k_out]=visibility(x)
n=length(x);
k=zeros(n,1);
k_in=zeros(n,1);
k_out=zeros(n,1);
NN=cell(n,1);
for i=1:n-1
    NN{i}=[NN{i} i+1];
    NN{i+1}=[NN{i+1} i];
    k(i)=k(i)+1;k(i+1)=k(i+1)+1;
    k_out(i) = k_out(i)+1;
    k_in(i+1) = k_in(i+1) +1;
    m = x(i+1)-x(i);
    for j=(i+2):n
        new_m= (x(j)-x(i))/(j-i);
        if m<new_m
            m=new_m;
            NN{i}=[NN{i} j];
            NN{j}=[NN{j} i];
            k(i)=k(i)+1;k(j)=k(j)+1;
            k_out(i)=k_out(i)+1;
            k_in(j)=k_in(j)+1;
        end
    end
end
% Compute txe degree distributions
% a1=max(k);
% a2=max(k_in);
% a3=max(k_out);
% xist=zeros(a1,1);
% xistin=zeros(a2,1);
% xistout=zeros(a3,1);
% %I don't count explicitely txe borders (1, and n)
% for i=2:n-1
% 	xist(k(i))=xist(k(i))+1;
% 	xistin(k_in(i))=xistin(k_in(i))+1;
% 	xistout(k_out(i))=xistout(k_out(i))+1;
% end
% ind=find(xist);
% indin=find(xistin);
% indout=find(xistout);
