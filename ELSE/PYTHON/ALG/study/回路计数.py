from math import gcd
n = int(input())
m = 1 << n
dp = [[0 for j in range(n)] for i in range(m)]
load = [[False for j in range(n)] for i in range(n)] 
for i in range(1, n + 1):
    for j in range(1, n + 1):
        if gcd(i, j) == 1:
            load[i - 1][j - 1] = True
dp[1][0] = 1
for i in range(1, m): 
    for j in range(n):
        if i >> j & 1: 
            for k in range(n): 
                if i - (1 << j) >> k & 1 and load[k][j]:  
                    dp[i][j] += dp[i - (1 << j)][k]
print(sum(dp[m - 1]) - dp[m - 1][0])