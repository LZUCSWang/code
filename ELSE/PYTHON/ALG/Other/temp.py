import math
import os
import sys
n = int(input())
data = [int(input()) for _ in range(n)]
t = data[0]
for i in data:
    t = math.gcd(t, i)
if t != 1:
    print("INF")
else:
    dp = [0]*10000
    dp[0] = 1
    for i in range(n):
        for j in range(data[i], 10000):
            dp[j] = max(dp[j], dp[j-data[i]])
    print(10000-sum(dp))
# 请在此输入您的代码
