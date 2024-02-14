import os
import sys
import math
# 请在此输入您的代码

dp=[float('inf') for _ in range(2022)]
for i in range(2,23):
    dp[i]=i
for i in range(23,2022):
    for j in range(i-21,i):
        dp[i]=min(dp[i],dp[j]+i*j//math.gcd(i,j))
print(dp[2021])
