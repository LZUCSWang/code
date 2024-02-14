import os
import sys
n = int(input())


def deal(s):
    flag = 0
    if len(s) == 22:
        if s[-2] == '1':
            flag = 1
        else:
            flag = 2
    datas, b = int(s[:2])*3600+int(s[3:5])*60 + \
        int(s[6:8]), int(s[9:11])*3600+int(s[12:14])*60+int(s[15:17])
    b += flag*3600*24
    return abs(datas-b)


for i in range(n):
    s1, s2 = input(), input()
    cnt = ((deal(s1)+deal(s2))//2) % (24*3600)
    ah, am, ase = cnt//3600, cnt//60 % 60, cnt % 60
    print("%02d:%02d:%02d" % (ah, am, ase))
# 请在此输入您的代码
