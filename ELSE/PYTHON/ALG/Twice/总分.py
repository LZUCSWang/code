m,n=map(int,input().split())
w,v=[0]*n ,[0]*n
dp=[0]*(m+1)
import sys
for i in range(n):
    v[i],w[i]=map(int,sys.stdin.readline().split())
for i in range(n):
    for j in range(w[i],m+1):
        dp[j]=max(dp[j],dp[j-w[i]]+v[i])
print(dp[-1])