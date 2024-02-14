import os
import sys
n, m = map(int, input().split())
data = [list(input().split()) for _ in range(n)]
x1, y1, x2, y2 = map(int, input().split())
queue = []
if data[x1-1][y1-1] == '0' or data[x2-1][y2-1] == '0':
    print(-1)
    sys.exit()
queue.append((x1-1, y1-1, 0))
data[x1-1][y1-1] = '0'
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
while len(queue):
    item = queue.pop(0)
    x, y, t = item[0], item[1], item[2]
    for d in flags:
        nx, ny = d[0]+x, d[1]+y
        if nx >= 0 and ny >= 0 and nx < n and ny < m and data[nx][ny] == '1':
            if nx == x2-1 and ny == y2-1:
                print(t+1)
                sys.exit()
            data[nx][ny] = '0'
            queue.append((nx, ny, t+1))
# 请在此输入您的代码
