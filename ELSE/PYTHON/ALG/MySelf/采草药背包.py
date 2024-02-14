import sys
s, n = map(int, sys.stdin.readline().split())
w, v, dp = [0]*(n+1), [0]*(n+1), [0]*(s+1)
for i in range(1, n+1):
    w[i], v[i] = map(int, sys.stdin.readline().split())
for i in range(1, n+1):
    for j in range(s, w[i]-1,-1):
        dp[j] = max(dp[j], dp[j-w[i]]+v[i])
print(dp[s])
print(dp)
