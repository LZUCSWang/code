m, n = map(int, input().split())
data = []
queue = []
for i in range(m):
    data.append(list(input()))
k = int(input())
for i in range(m):
    for j in range(n):
        if data[i][j] == 'g':
            queue.append((i, j))
flags = [(0, 1), (0, -1), (1, 0), (-1, 0)]


def bfs():
    global k
    t = len(queue)
    while t > 0:
        temp = queue.pop(0)
        x1, y1 = temp[0], temp[1]
        for d in flags:
            nx = x1+d[0]
            ny = y1+d[1]
            if nx >= 0 and nx < m and ny >= 0 and ny < n and data[nx][ny] == '.':
                data[nx][ny] = 'g'
                queue.append((nx, ny))
        t -= 1


for i in range(k):
    bfs()
for i in range(m):
    print(''.join(data[i]))
