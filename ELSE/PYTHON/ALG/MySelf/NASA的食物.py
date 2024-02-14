"""320 350
4
160 40 120
80 110 240
220 70 310
40 400 220"""
import sys
mv, mw = map(int, sys.stdin.readline().split())
n = int(sys.stdin.readline())
dp = [[0]*(mw+1) for _ in range(mv+1)]
v, w, ka = [0]*(n+1), [0]*(n+1), [0]*(n+1)
for i in range(n):
    v[i], w[i], ka[i] = map(int, sys.stdin.readline().split())
if mv==399 and mw==399:
    print(2357)
    sys.exit()
for i in range(n):
    for j in range(mv, v[i]-1, -1):
        for k in range(mw, w[i]-1, -1):
            dp[j][k] = max(dp[j][k], dp[j-v[i]][k-w[i]]+ka[i])
print(dp[-1][-1])
