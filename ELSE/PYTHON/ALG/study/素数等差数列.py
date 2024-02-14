import os
import sys
rightnums = 0
cntshou = 0
cntcha = 0


def judge(n) -> bool:
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

for shou in range(2, 1000000000):
    if judge(shou) == True:
        for cha in range(2, 1000):
            rightnums=0
            for test in range(shou+cha, cha*11, cha):
                if judge(test) == True:
                    rightnums += 1
            if rightnums == 9:
                cntshou = shou
                cntcha = cha
                break
    if cntshou != 0:
        break
if cntshou != 0:
    print(cntcha)
else:
    print(0)
# 请在此输入您的代码
