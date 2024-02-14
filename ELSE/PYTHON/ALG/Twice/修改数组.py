import os
import sys
n = int(input())
data = list(map(int, input().split()))
seen = [0]*(1000000)
for i in range(n):
    if seen[data[i]] == 0:
        seen[data[i]] = 1
        continue
    while seen[data[i]] == 1:
        data[i] += 1
    seen[data[i]]=1
print(*data)

# 请在此输入您的代码
