#寒假作业
from itertools import permutations as p
cnt=0
for item in p([i for i in range(1,14)]):
    if item[0]+item[1]==item[2] and item[3]-item[4]==item[5] and item[6]*item[7]==item[8] and item[9]%item[10]==0 and item[9]//item[10]==item[11]:
        cnt+=1
print(cnt)
