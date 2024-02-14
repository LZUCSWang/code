n, m = map(int, input().split())
data = []
for i in range(n):
    data.append(list(input()))
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def slove(i, j):
    data[i][j] = '0'
    queue = []
    queue.append((i, j))
    while len(queue) > 0:
        item = queue.pop(0)
        x, y = item[0], item[1]
        for d in flags:
            nx, ny = x+d[0], y+d[1]
            if nx >= 0 and ny >= 0 and nx < n and ny < m and data[nx][ny] != '0':
                data[nx][ny] = '0'
                queue.append((nx, ny))


cnt = 0
for i in range(n):
    for j in range(m):
        if data[i][j] != '0':
            cnt += 1
            slove(i, j)
print(cnt)
