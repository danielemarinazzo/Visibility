function [ MI_visibility, Hdata1,Hdata2 ] = Mutual_information_visibility( vector1,vector2)
%[ MI_visibility ] = Mutual_information_visibility( vector1,vector2)
%   MI_visibility= mutual information between vector 1 and vector 2
%vector=data
% Caroline Garcia Forlim 25/04/2016 - quel.caroline@gmail.com

%% joint probability set
joint_prob=zeros(max([max(vector1) max(vector2)]),max([max(vector1) max(vector2)]));
for i=1:length(vector1)
    
    joint_prob(vector1(i),vector2(i))= joint_prob(vector1(i),vector2(i))+1;
    
end
joint_prob=joint_prob./length(vector1);

%% mutual information
MI_visibility=0;
Hdata1=0;
Hdata2=0;

for i=1: size(joint_prob,1)
    for j= 1:size(joint_prob,2)
        if joint_prob(i,j)~=0
            MI_visibility=MI_visibility + (joint_prob(i,j)*log2(joint_prob(i,j)/(sum(joint_prob(i,:))*sum(joint_prob(:,j)))));
        end
    end
%     if sum(joint_prob(i,:))~=0
%     Hdata1=Hdata1+ sum(joint_prob(i,:))*log2(1/(sum(joint_prob(i,:))));
%     end
%     if sum(joint_prob(:,i))~=0
%     Hdata2=Hdata2+ sum(joint_prob(:,i))*log2(1/(sum(joint_prob(:,i))));
%     end
end


end

