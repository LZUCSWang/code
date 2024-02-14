n, v = map(int, input().split())
wei, val = [0]*(n+1), [0]*(n+1)
dp = [0]*(v+1)
for i in range(1, n+1):
    wei[i], val[i] = map(int, input().split())
for i in range(1, n+1):
    for j in range(v, wei[i]-1, -1):
        dp[j] = max(dp[j], dp[j-wei[i]]+val[i])
print(dp[-1])
