t, m = map(int, input().split())
data = [tuple(map(int, input().split())) for _ in range(m)]
dp = [0]*(t+1)
for i in range(m):
    for j in range(t, data[i][0]-1, -1):
        dp[j] = max(dp[j], dp[j-data[i][0]]+data[i][1])
print(dp[-1])
