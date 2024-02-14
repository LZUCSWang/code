import itertools as it
import os
import sys
from tkinter import S

# 请在此输入您的代码
allline = int(input())
allitem = []
allvalue = []
for i in range(allline):
    inputstr = input().split()
    temp = []
    for j in range(i+1):
        temp.append(int(inputstr[j]))
    allitem.append(temp)
s = list(it.product(range(2), repeat=allline-1))
print(s)
for item in range(allline):
    nums = allitem[0][0]
    hang = 0
    lie = 0
    for dong in range(allline-1):
        if s[item][dong] == 1:
            lie += 1、】
18        hang += 1
        nums += allitem[hang][lie]
    allvalue.append(nums)
print(min(allvalue))
