import os
import sys
n = int(input())
arry = list(map(int, input().split()))
aset = set()
aset.add(arry[0])
for i in range(1, len(arry)):
    temp = arry[i]
    while temp in aset:
        temp += 1
    aset.add(temp)
    arry[i] = temp
print(' '.join(map(str, arry)))
# 请在此输入您的代码
