#算式问题
cnt=0
from itertools import permutations
for first in range(123,800):
    tf=str(first)
    if len(set(list(tf)))==3 and '0' not in tf:
        for second in range(first,900):
            tfs=tf+str(second)
            if len(set(list(tfs)))==6 and '0' not in tfs:
                for third in range(second,999):
                    tfst=tfs+str(third)
                    if len(set(list(tfst)))==9 and '0' not in tfst and first+second==third:
                        cnt+=2
                        print(first,second,third)
print(cnt)
