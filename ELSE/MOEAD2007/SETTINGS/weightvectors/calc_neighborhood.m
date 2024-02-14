function [A, I] = calc_neighborhood(fn)

data  = load(fn);
count = size(data, 1);
for i=1:count
    dist(i,i) = 0;
    for j=i+1:count
        dist(i,j) = norm(data(i,:) - data(j,:));
        dist(j,i) = dist(i,j);
    end
end

%size(dist)
%dist
[A, I] = sort(dist, 1, 'ascend');

fn2 = strcat('ID-',fn);

fid = fopen(fn2,'wt');

niche = fix(0.2*count);

for i=1:count
    fprintf(fid,'%5d  ',I(:,i)');
    fprintf(fid,'\n');
end
fclose(fid);

% figure
% hold on
% plot3(data(id,1),data(id,2),data(id,3),'*')
% plot3(data(I(1:niche,id),1),data(I(1:niche,id),2),data(I(1:niche,id),3),'o')
