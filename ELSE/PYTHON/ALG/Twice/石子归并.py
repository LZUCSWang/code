n = int(input())
# dp[i][j]为i堆到j堆的石子数量
dp = [[0]*(n+1) for _ in range(n+1)]
sum = [0]*(n+1)
for i in range(1, n+1):
    sum[i] = sum[i-1]+int(input())
for i in range(1, n):
    for j in range(1, n):
        r=j+i
        if r>n:
            continue
        dp[j][r] = float('inf')
        for k in range(j, r):
            dp[j][r] = min(dp[j][r], dp[j][k]+dp[k+1][r]+sum[r]-sum[j-1])
print(dp[1][n])
