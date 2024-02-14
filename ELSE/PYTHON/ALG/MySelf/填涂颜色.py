import sys
n = int(input())
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
data = [list(map(int, input().split())) for _ in range(n)]


def bfs(i, j):
    seen = [[0]*n for _ in range(n)]
    queue = [(i, j)]
    seen[i][j] = 1
    while len(queue) > 0:
        item = queue.pop(0)
        x, y = item[0], item[1]
        for d in flags:
            nx, ny = x+d[0], y+d[1]
            if nx >= n or nx < 0 or ny >= n or ny < 0:
                return
            if seen[nx][ny] == 0 and data[nx][ny] != 1:
                seen[nx][ny] = 1
                queue.append((nx, ny))
    for i in range(n):
        for j in range(n):
            if seen[i][j] == 1:
                data[i][j] = 2
            print(data[i][j], end=' ')
        print()
    sys.exit()


for i in range(n):
    for j in range(n):
        if data[i][j] == 0:
            bfs(i, j)
