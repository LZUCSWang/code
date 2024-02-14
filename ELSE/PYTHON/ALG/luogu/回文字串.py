s = '0'+input()
n = len(s)-1
dp = [[0]*(n+1) for _ in range(n+1)]
for jiange in range(2, n+1):
    for l in range(1, n-jiange+2):
        r = l+jiange-1
        dp[l][r] = dp[l+1][r -1] if s[l] == s[r] else min(dp[l+1][r], dp[l][r-1])+1
print(dp[1][n])
