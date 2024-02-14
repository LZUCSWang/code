n, m = map(int, input().split())
datas = [[0]*(m+1)]
for i in range(n):
    datas.append([0]+list(map(int, input().split())))
cnt = []
queue = []
done = [[0]*(m+1) for _ in range(n+1)]
used = [[0]*(m+1) for _ in range(n+1)]
flags = [(0, 0), (1, 0), (0, 1), (1, 1), (-1, -1),
        (-1, 0), (-1, 1), (0, -1), (1, -1)]
def check(x, y) -> int:
    temp = 0
    for i in range(4):
        nx, ny = x+flags[i][0], y+flags[i][1]
        if done[nx][ny] == 0:
            if temp == 0:
                temp = datas[nx][ny]
            elif temp != datas[nx][ny]:
                return -1
    return temp
def slove():
    for i in range(1, n):
        for j in range(1, m):
            if check(i, j) >= 0:
                queue.append((i, j))
                used[i][j] = 1
    while len(queue) > 0:
        item = queue.pop(0)
        x, y = item[0], item[1]
        chk = check(x, y)
        if chk > 0:
            for i in range(4):
                done[x+flags[i][0]][y+flags[i][1]] = 1
            cnt.append((x, y, chk))
        for i in range(1, 9):
            nx, ny = x+flags[i][0], y+flags[i][1]
            if nx > 0 and nx < n and ny > 0 and ny < m and used[nx][ny] == 0 and check(nx, ny) >= 0:
                queue.append((nx, ny))
                used[nx][ny] = 1
    for i in range(1, n+1):
        for j in range(1, m+1):
            if done[i][j] == 0:
                print(-1)
                return
    print(len(cnt))
    for i in range(len(cnt)-1, -1, -1):
        print(cnt[i][0], cnt[i][1], cnt[i][2])
slove()
