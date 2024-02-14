n = int(input())
data = [list(input()) for _ in range(n)]
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
seen = [[0]*n for _ in range(n)]

gaodi = 0


def bfs(i, j):
    global flag
    queue = [(i, j)]
    while len(queue):
        item = queue.pop(0)
        x, y = item[0], item[1]
        if (x==0 or data[x-1][y]=='#') and (x==n-1 or data[x+1][y]=='#') and (y==0 or data[x][y-1]=='#') and (y==n-1 or data[x][y+1]=='#') and not flag:
            flag=True
        for d in flags:
            nx, ny = x+d[0], y+d[1]
            if nx >= 0 and ny >= 0 and nx < n and ny < n and data[nx][ny] == '#' and seen[nx][ny] == 0:
                    queue.append((nx, ny))
                    seen[nx][ny] = 1


for i in range(n):
    for j in range(n):
        if seen[i][j] == 0 and data[i][j] == '#':
            flag=False
            seen[i][j] = 1
            bfs(i, j)
            if flag:
                gaodi += 1
print(gaodi)
