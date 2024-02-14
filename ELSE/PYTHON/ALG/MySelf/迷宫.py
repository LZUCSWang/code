n, m, t = map(int, input().split())
s1, s2, e1, e2 = map(int, input().split())
seen = [[0]*(m+1) for _ in range(n+1)]
seen[s1][s2]=1
for i in range(t):
    datas, b = map(int, input().split())
    seen[datas][b] = 1
    if datas == 1:
        for j in range(b, m+1):
            seen[1][j] = 1
    if b == 1:
        for j in range(datas, n+1):
            seen[j][1] = 1
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
cnt = 0
def dfs(x, y):
    global cnt
    if x == e1 and y ==e2:
        cnt += 1
        return
    for d in flags:
        nx, ny = d[0]+x, d[1]+y
        if nx > 0 and nx <= n and ny > 0 and ny <= m and seen[nx][ny] == 0:
            seen[nx][ny] = 1
            dfs(nx, ny)
            seen[nx][ny] = 0
dfs(s1, s2)
print(cnt)
