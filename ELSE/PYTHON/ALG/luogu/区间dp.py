n=int(input())
data=[0]+[int(input()) for _ in range(n)]
dp=[[0]*(n+1) for _ in range(n+1)]
for i in range(1,n+1):
    dp[i][i]=data[i]*n
for jiange in range(2,n+1):
    for left in range(1,n-jiange+2):
        right=left+jiange-1
        dp[left][right]=max(dp[left][right-1]+data[right]*(n-jiange+1),dp[left+1][right]+data[left]*(n-jiange+1))
print(dp[1][n])