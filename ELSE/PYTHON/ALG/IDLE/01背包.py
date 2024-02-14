#01背包
n,m=map(int,input().split())
dp=[0]*(m+1)
w,v=[0]*n,[0]*n
for i in range(n):
    w[i],v[i]=map(int,input().split())
for i in range(n):
    for j in range(m,w[i]-1,-1):
        dp[j]=max(dp[j],dp[j-w[i]]+v[i])
print(dp[-1])
