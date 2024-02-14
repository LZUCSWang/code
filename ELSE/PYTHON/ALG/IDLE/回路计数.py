#回路计数
#dp[i][j] 最后一次到的楼是j楼，此时记录为i的方案数
zonglou=15
m=(1<<zonglou)-1
dp=[[0]*(m+1) for _ in range(zonglou+1)]
graph=[[0]*(zonglou+1) for _ in range(zonglou+1)]
from math import gcd as g
for i in range(1,zonglou+1):
    for j in range(i+1,zonglou+1):
        if g(i,j)==1:
            graph[i][j]=True
            graph[j][i]=True
dp[1][1]=1
for zhuangtai in range(1,m+1):
    for lou in range(1,zonglou+1):
        if zhuangtai&(1<<lou-1):
            for nextlou in range(1,zonglou+1):
                if zhuangtai&(1<<(nextlou-1)) ==0 and graph[nextlou][lou]:
#                    print(zhuangtai,lou,nextlou,bin(zhuangtai+(1<<nextlou-1)))
                    dp[nextlou][zhuangtai+(1<<nextlou-1)]+=dp[lou][zhuangtai]
cnt=0
for j in range(1,zonglou+1):
    cnt+=dp[j][m]
print(cnt)
