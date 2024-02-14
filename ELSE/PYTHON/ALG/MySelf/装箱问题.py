m = int(input())
dp = [0]*(m+1)
n = int(input())
data = [int(input()) for _ in range(n)]
for i in range(n):
    for j in range(m, data[i]-1, -1):
        dp[j] = max(dp[j], dp[j-data[i]]+data[i])
print(m-dp[-1])
