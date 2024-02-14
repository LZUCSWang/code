#路径
from math import gcd as g
n=2021
def lcm(datas,b):
    return datas*b//g(datas,b)
dp=[float('inf')]*(n+1)
graph=[[float('inf')]*(n+1) for _ in range(n+1)]
for i in range(1,23):
    graph[1][i]=i
    dp[i]=i
for i in range(23,n+1):
    for j in range(i-21,i):
        graph[j][i]=lcm(j,i)
for i in range(23,n+1):
    for j in range(1,22):
        dp[i]=min(dp[i],dp[i-j]+graph[i-j][i])
            
print(dp[n])
