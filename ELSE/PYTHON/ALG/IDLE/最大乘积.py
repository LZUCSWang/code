#最大乘积
from itertools import permutations as p
t=0
for i in p([i for i in range(1,10)]):
    i=list(i)
    for cheng in range(1,9):
        cnt=int(''.join(list(map(str,i[:cheng]))))*int(''.join(list(map(str,i[cheng:]))))
        if '0' in str(cnt) or len(set(list(str(cnt))))!=9:
            continue
        t=max(t,cnt)
print(t)
        
