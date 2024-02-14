n, m = map(int, input().split())
data = [tuple(map(int, input().split())) for _ in range(n)]
dp = [0]*(m+1)
for i in range(n):
    for j in range(m, -1, -1):
        if data[i][2] <= j:
            dp[j] = max(dp[j]+data[i][0], dp[j-data[i][2]]+data[i][1])
        else:
            dp[j] += data[i][0]
print(dp[-1]*5)
