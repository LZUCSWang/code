import os
import sys
import math
n = int(input())


def d(datas, b):
    return ((datas[0]-b[0])**2 + (datas[1]-b[1])**2)**0.5


for i in range(n):
    data = [tuple(map(int, input().split())) for _ in range(3)]
    datas = d(data[0], data[1])
    b = d(data[0], data[2])
    c = d(data[1], data[2])
    p = (datas+b+c)*0.5
    area = math.sqrt(p*(p-datas)*(p-b)*(p-c))
    print("%.2f" % area)

# 请在此输入您的代码
