import sys
n = int(input())
data = [[]]
for i in range(n):
    data.append(list('2'+sys.stdin.readline()))
x1, y1, x2, y2 = map(int, input().split())
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
queue = []
queue.append((x1, y1, 0))
data[x1][y1] = '1'
while len(queue) > 0:
    item = queue.pop(0)
    x, y, t = item[0], item[1], item[2]
    for d in flags:
        nx, ny = x+d[0], y+d[1]
        if nx > 0 and ny > 0 and nx <= n and ny <= n and data[nx][ny] == '0':
            if nx == x2 and ny == y2:
                print(t+1)
                sys.exit()
            data[nx][ny] = '1'
            queue.append((nx, ny, t+1))
