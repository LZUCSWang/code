import sys
n, m = map(int, sys.stdin.readline().split())
data = []
flag = 0
for i in range(n):
    data.append(list(sys.stdin.readline()))
    if flag:
        continue
    if 'm' in data[-1]:
        x, y = i, data[-1].index('m')
        flag = 1
queue = []
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
queue.append((x, y, 0))
data[x][y] = '#'
while len(queue) > 0:
    item = queue.pop(0)
    x, y, t = item[0], item[1], item[2]
    for d in flags:
        nx, ny = d[0]+x, d[1]+y
        if nx >= 0 and ny >= 0 and nx < n and ny < m and data[nx][ny] != '#':
            if data[nx][ny] == 'd':
                print(t+1)
                sys.exit()
            data[nx][ny] = '#'
            queue.append((nx, ny, t+1))
