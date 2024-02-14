import os
import sys
n, m, q = map(int, input().split())
data = [[float('inf')]*(n+1) for _ in range(n+1)]
for i in range(m):
    datas, b, c = map(int, input().split())
    data[datas][b] = c
    data[b][datas] = c
for k in range(n):
    for i in range(1, n+1):
        for j in range(1, n+1):
            if data[i][j] > data[i][k]+data[k][j]:
                data[i][j] = data[i][k]+data[k][j]
for i in range(q):
    datas, b = map(int, input().split())
    print(data[datas][b])
# 请在此输入您的代码
