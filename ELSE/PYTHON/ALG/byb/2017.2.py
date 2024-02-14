import os
import sys
data = """UDDLUULRUL
UURLLLRRRU
RRUURLDLRD
RUDDDDUUUU
URUDLLRRUU
DURLRLDLRL
ULLURLLRDU
RDLULLRDDD
UUDDUDUDLL
ULRDLUURRR""".split()
m, n = len(data), len(data[0])
cnt = 0


def slove(x, y):
    if x >= n or x < 0 or y >= n or y < 0:
        global cnt
        cnt += 1
        return True
    if flag[x][y] == 1:
        return False
    flag[x][y] = 1
    if data[x][y] == 'U':
        slove(x-1, y)
    elif data[x][y] == 'D':
        slove(x+1, y)
    elif data[x][y] == 'R':
        slove(x, y+1)
    elif data[x][y] == 'L':
        slove(x, y-1)
    return False


for i in range(m):
    for j in range(n):
        flag = [[0]*n for _ in range(m)]
        slove(i, j)
print(cnt)

# 请在此输入您的代码
