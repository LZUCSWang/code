import os
import sys
n = int(input())
data = list(map(int, input().split()))
data.sort(reverse=True)
data = [0]+data
dp = [[0]*(sum(data)+1) for _ in range(n+1)]
for i in range(1, n+1):
    for j in range(sum(data)+1):
        if dp[i-1][j] == 1:
            dp[i][j] = 1
            dp[i][j+data[i]] = 1
            if j > data[i]:
                dp[i][j-data[i]] = 1
print(sum(dp[-1])-1)
# 请在此输入您的代码
