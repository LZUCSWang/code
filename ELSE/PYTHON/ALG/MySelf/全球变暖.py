n = int(input())
data = [input() for _ in range(n)]
flags = [(0, 1), (1, 0), (-1, 0), (0, -1)]
queue = []
cnt = 0
flag = 0
seen = [[0]*n for _ in range(n)]


def check(x, y):
    global cnt, n, flag
    if flag == 0 and (x+1 >= n or data[x+1][y] == '#') and (x-1 < 0 or data[x-1][y] == '#') and (y+1 >= n or data[x][y+1] == '#') and (y-1 < 0 or data[x][y-1] == '#'):
        cnt += 1
        flag = 1


for i in range(n):
    for j in range(n):
        if data[i][j] == '#' and seen[i][j] == 0:
            queue.append((i, j))
            seen[i][j] = 1
            flag = 0
            while len(queue) > 0:
                now = queue.pop(0)
                check(now[0], now[1])
                for d in flags:
                    nx, ny = now[0]+d[0], now[1]+d[1]
                    if nx >= n or nx < 0 or ny >= n or ny < 0:
                        continue
                    if data[nx][ny] == '#' and seen[nx][ny]==0:
                        queue.append((nx, ny))
                        seen[nx][ny] = 1
print(cnt)
