n,m=map(int,input().split())
data=[0]+list(map(int,input().split()))
dp=[[0]*(m+1) for _ in range(n+1)]
for i in range(1,n+1):
    for j in range(1,m+1):
        if j>data[i]:
            dp[i][j]=dp[i-1][j]+dp[i-1][j-data[i]]
        elif j==data[i]:
            dp[i][j]=dp[i-1][j]+1
        elif j<data[i]:
            dp[i][j]=dp[i-1][j]
print(dp[-1][-1])
        