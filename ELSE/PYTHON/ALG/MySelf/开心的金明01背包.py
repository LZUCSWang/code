m, n = map(int, input().split())
dp = [0]*(m+1)
w = [0]*(n+1)
v = [0]*(n+1)
for i in range(n):
    datas, b = map(int, input().split())
    w[i], v[i] = datas, datas*b
for i in range(n):
    for j in range(m, w[i]-1, -1):
        dp[j] = max(dp[j], dp[j-w[i]]+v[i])
print(dp[-1])
