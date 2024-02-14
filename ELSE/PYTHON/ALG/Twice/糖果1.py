n, m, k = map(int, input().split())
data = [0]*n
for i in range(n):
    temp = tuple(map(int, input().split()))
    for j in range(k):
        data[i] = data[i] | (1 << temp[j]-1)
dp = [float('inf')]*(1 << m)
dp[0] = 0
for i in range(n):
    for j in range(1 << m):
        dp[j | data[i]] = min(dp[j | data[i]], dp[j]+1)
print(dp[(1 << m)-1])
