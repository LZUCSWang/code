n, m, q = map(int, input().split())
s, t, x, y = map(int, input().split())
x, y, dx, dy, cnt = x-1, y-1, 1, 1, 0
bomb = [[0]*m for _ in range(n)]
for i in range(q):
    datas, b = map(int, input().split())
    bomb[b-1][datas-1] = 1
visited = [[[[0]*3 for _ in range(3)] for _ in range(m)] for _ in range(n)]
visited[x][y][dx+1][dy+1] = 1
for i in range(x, x+t):
    for j in range(y, y+s):
        cnt += bomb[j][i]
        bomb[j][i] = 0
while True:
    if x+dx < 0 or x+t+dx-1 >= m:
        dx *= -1
    if y+dy < 0 or y+s+dy-1 >= n:
        dy *= -1
    x, y = x+dx, y+dy
    if visited[x][y][dx+1][dy+1]:
        break
    visited[x][y][dx+1][dy+1] = 1
    for i in range(x, x+t):
        if dy == 1:
            cnt += bomb[y+s-1][i]
            bomb[y+s-1][i] = 0
        else:
            cnt += bomb[y][i]
            bomb[y][i] = 0
    for i in range(y, y+s):
        if dx == 1:
            cnt += bomb[i][x+t-1]
            bomb[i][x+t-1] = 0
        else:
            cnt += bomb[i][x]
            bomb[i][x] = 0
print(cnt)
