n, m = map(int, input().split())
data = [list(input()) for _ in range(n)]
queue = []

flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
for i in range(m):
    i, j = map(int, input().split())
    seen = [[0]*n for _ in range(n)]
    seen[i-1][j-1] = 1
    queue.append((i-1, j-1, 1))
    cnt = 0
    while len(queue) > 0:
        item = queue.pop(0)
        x, y, t = item[0], item[1], item[2]
        cnt = max(cnt, t)
        for d in flags:
            nx, ny = d[0]+x, d[1]+y
            if nx >= 0 and ny >= 0 and nx < n and ny < n and data[x][y]!=data[nx][ny] and seen[nx][ny] == 0:
                seen[nx][ny] = 1
                queue.append((nx, ny, t+1))
    print(cnt+1)
