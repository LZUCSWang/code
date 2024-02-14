#包子凑数
n=int(input())
dp=[0]*10000000
dp[0]=1
data=[int(input()) for _ in range(n)]
from math import gcd as g
gg=data[0]
for i in range(1,n):
    gg=g(gg,data[i])
if gg!=1:
    print('INF')
    import sys
    sys.exit()
for i in range(n):
    for j in range(data[i],10000000):
        if dp[j-data[i]]==1:
            dp[j]=1
print(dp.count(0))
