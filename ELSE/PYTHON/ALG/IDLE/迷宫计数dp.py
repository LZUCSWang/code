#迷宫计数dp
import sys
n,m=map(int,input().split())
dp=[[float('inf')]*(n+1) for _ in range(n+1)]
for i in range(m):
    x,y=map(int,input().split())
    if x==n and y==n:
        print(0)
        sys.exit()
    dp[x][y]=0
dp[1][1]=1
for i in range(1,n+1):
    for j in range(1,n+1):
        if dp[i][j]==0 or i==1 and j==1:
            continue
        if i==1:
            dp[1][j]=dp[1][j-1]
        elif j==1:
            dp[i][1]=dp[i-1][1]
        else:
            dp[i][j]=dp[i-1][j]+dp[i][j-1]
print(dp[n][n])
    
