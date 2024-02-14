# dp[i][j]最后到达j号楼，且当前状态为i。
import math
import sys
n = 21
# def dfs(x):
allowed = [[False]*(n+1) for _ in range(n+1)]
print(allowed)
for i in range(1, n+1):
    for j in range(1, n+1):
        if math.gcd(i, j) == 1:
            allowed[i][j] = allowed[j][i] = True
print(allowed[3][6])
print(allowed[2][5])
print(allowed[1][7])
print(str(bin((1 << n)-1)).count('1'))
dp = [[0]*(1 << n) for _ in range(n+1)]
dp[1][1] = 1
for i in range(1, 1 << n):
    for j in range(1, n+1):
        if i & (1 << j-1):
            for k in range(1, n+1):
                if i & (1 << k-1) == 0 and allowed[j][k]:
                    try:
                        dp[k][i+(1 << k-1)] += dp[j][i]
                    except:
                        print(k, bin(i+(1 << k-1)), j, bin(i))
                        sys.exit()
cnt = 0
for i in range(1, n+1):
    cnt += dp[i][(1 << n)-1]
print(cnt)
sys.exit()
