#pailie
from itertools import permutations as p
n=int(input())
cnt='0'
for i in p(input().split()):
    cnt=max(''.join(i),cnt)
print(cnt)
