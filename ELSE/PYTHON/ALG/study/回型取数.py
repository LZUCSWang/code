import os
import sys

# 请在此输入您的代码
m, n = map(int, input().split())
leflim,uplim=1,0
data=[]
flag=1
for i in range(m):
    data.append(list(map(int,input().split())))
i, j = 0, 0
while True:
    if data[i][j]==float("inf"):
        break
    print("%d " % (data[i][j]))
    data[i][j]=float("inf")
    if flag == 1:
        i += 1
        if i >= m:
            flag = 2
            i -= 1
            j += 1
            m-=1
    elif flag == 2:
        j += 1
        if j >= n:
            flag = 3
            i -= 1
            j -= 1
            n-=1
    elif flag == 3:
        i -= 1
        if i < uplim:
            flag = 4
            i += 1
            j -= 1
            uplim+=1
    elif flag == 4:
        j -= 1
        if j < leflim:
            flag = 1
            i += 1
            j += 1
            leflim+=1
