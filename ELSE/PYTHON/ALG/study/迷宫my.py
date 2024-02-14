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
cnt = 0
flag = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}
for i in range(10):
    for j in range(10):
        seen = [[0]*10 for _ in range(10)]
        x, y = i, j
        while seen[x][y] == 0:
            seen[x][y] = 1
            c = data[x][y]
            x, y = x+flag[c][0], y+flag[c][1]
            if x >= 10 or x < 0 or y >= 10 or y < 0:
                cnt += 1
                break
print(cnt)

# 请在此输入您的代码
