import os
import sys
s = list(input())
data = [0]*130
for i in s:
    data[ord(i)] += 1
print(chr(data.index(max(data))))
print(max(data))
# 请在此输入您的代码
