#没有上司的舞会
n=int(input())
#f(i,j)为i，0 为第i个人参加和 i,1为第i个人不参加
data=[0]+[int(input()) for _ in range(n)]
last=[[] for _ in range(n+1)]
flag=[True]*(n+1)
import sys
sys.setrecursionlimit(10000)
for i in range(n-1):
    l,k=map(int,input().split())
    flag[l]=False
    last[k].append(l)
def dfs(now):
    if len(last[now])==0:
        dp[now][1]=data[now]
        dp[now][0]=0
        return
    dp[now][1]=data[now]
    for son in last[now]:
        dfs(son)
        dp[now][1]+=dp[son][0]
        dp[now][0]+=max(dp[son][1],dp[son][0])
dp=[[0]*2 for _ in range(n+1)]
for i in range(1,n+1):
    if flag[i]:
        cnt=i
        break
dfs(cnt)
"""for i in range(1,n+1):
    print(*dp[i])"""
print(max(dp[cnt][1],dp[cnt][0]))
