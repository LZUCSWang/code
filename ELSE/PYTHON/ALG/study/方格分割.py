seen = [[0]*7 for _ in range(7)]
seen[3][3] = 1
flags = [(0, 1), (0, -1), (1, 0), (-1, 0)]
cnt = 0


def dfs(x, y):
    global cnt
    if x == 0 or x == 6 or y == 0 or y == 6:
        cnt += 1
        return
    seen[x][y], seen[6-x][6-y] = 1, 1
    for d in flags:
        nx, ny = x+d[0], y+d[1]
        if seen[nx][ny] == 0:
            dfs(nx, ny)
    seen[x][y], seen[6-x][6-y] = 0, 0


dfs(3, 3)
print(cnt//4)
