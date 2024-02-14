function gen_weight(nobj, H)

[a] = gen_weightRecursive(nobj, H);  
%plot3(a(:,1),a(:,2),a(:,4),'.'); 

size(a,1)

fn = strcat('W',num2str(nobj),'-H',num2str(H),'.dat');

save(fn,'a','-ascii')

