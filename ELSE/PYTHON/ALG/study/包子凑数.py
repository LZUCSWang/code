import os
import sys
import math
N = 10000
n = int(input())
data = [int(input()) for _ in range(n)]
t = data[0]
for i in range(n):
    t = math.gcd(t, data[i])
if t != 1:
    print("INF")
else:
    dp = [0]*N
    dp[0] = 1
    for i in range(n):
        for j in range(data[i], N):
            dp[j] = max(dp[j], dp[j-data[i]])
    print(N-sum(dp))
# 请在此输入您的代码
