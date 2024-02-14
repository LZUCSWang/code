import os
import sys

# 请在此输入您的代码
s = list(input())
t = int(input())
cnt = 0
while cnt < t:
    if s[1] < s[0]:
        del s[0]
    else:
        del s[1]
    cnt += 1

print(''.join(s),end='')