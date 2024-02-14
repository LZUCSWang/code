"""3 58
2
1 4
1 6
1
4 9
2
5 5
4 5"""
n,m=map(int,input().split())
w,v,dp=[0]*10000,[0]*10000,[0]*(m+1)
for i in range(n):
  t=int(input())
  for j in range(t):
    w[j],v[j]=map(int,input().split())
  for k in range(m,-1,-1):
    for x in range(t):
      if k>=w[x]:
        dp[k]=max(dp[k],dp[k-w[x]]+v[x])
print(dp[-1])