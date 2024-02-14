import os
import sys
n = int(input())
last = list(map(int, input().split()))
for i in range(1, n):
    temp = list(map(int, input().split()))
    for j in range(i+1):
        if j == 0:
            temp[0] += last[0]
        elif j == i:
            temp[j] += last[-1]
        else:
            temp[j] = temp[j]+max(last[j-1], last[j])
    last = temp
    print(temp)
if n % 2 == 1:
    print(temp[n//2])
else:
    print(max(temp[n//2], temp[n//2-1]))


# 请在此输入您的代码
