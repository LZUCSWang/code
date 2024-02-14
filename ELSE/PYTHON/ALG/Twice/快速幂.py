import os
import sys
datas, b, c = map(int, input().split())
cnt = 1
while b:
    if b & 1:
        cnt *= datas
        cnt %= c
    datas *= datas
    datas %= c
    b >>= 1
print(cnt)
# 请在此输入您的代码
