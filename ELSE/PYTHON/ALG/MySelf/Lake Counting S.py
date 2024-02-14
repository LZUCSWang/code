n, m = map(int, input().split())
data = [input() for _ in range(n)]
flags = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (1, -1), (-1, -1), (-1, 1)]
queue = []
seen = [[0]*m for _ in range(n)]


def bfs(i, j):
    queue.append((i, j))
    seen[i][j] = 1
    while len(queue) > 0:
        item = queue.pop(0)
        x, y = item[0], item[1]
        for d in flags:
            nx, ny = x+d[0], y+d[1]
            if nx >= 0 and nx < n and ny >= 0 and ny < m and data[nx][ny] == 'W' and seen[nx][ny] == 0:
                seen[nx][ny] = 1
                queue.append((nx, ny))


cnt = 0
for i in range(n):
    for j in range(m):
        if data[i][j] == 'W' and seen[i][j] == 0:
            cnt += 1
            bfs(i, j)
print(cnt)
