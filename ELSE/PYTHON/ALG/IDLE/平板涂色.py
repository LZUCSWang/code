#平板涂色
target=input()
n=len(target)
target='0'+target
dp=[[float('inf')]*(n+1) for _ in range(n+1)]
for i in range(1,n+1):
    dp[i][i]=1
for jiange in range(2,n+1):
    for left in range(1,n-jiange+2):
        right=left+jiange-1
        if target[right]==target[left]:
            dp[left][right]=min(dp[left+1][right],dp[left][right-1])
        else:
            for k in range(left,right):
                dp[left][right]=min(dp[left][right],dp[left][k]+dp[k+1][right])
print(dp[1][n]-1)
