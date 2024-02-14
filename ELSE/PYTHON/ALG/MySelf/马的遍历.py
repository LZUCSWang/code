import copy
m, n, ax, ay = map(int, input().split())
dp = [[0]*(n+1) for _ in range(m+1)]
seen = copy.deepcopy(dp)
seen[ax][ay] = 1
flags = [(1, 2), (2, 1), (-1, 2), (-2, 1), (1, -2), (2, -1), (-1, -2), (-2, -1)]
queue = [(ax, ay, 0)]
while len(queue) > 0:
    item = queue.pop(0)
    x, y, s = item[0], item[1], item[2]
    for d in flags:
        nx, ny = x+d[0], y+d[1]
        if nx > 0 and nx <= m and ny > 0 and ny <= n and seen[nx][ny] == 0:
            seen[nx][ny] = 1
            queue.append((nx, ny, item[2]+1))
            dp[nx][ny] = item[2]+1
for i in range(1, m+1):
    for j in range(1, n+1):
        print("%-5d" % dp[i][j], end='') if dp[i][j] != 0 or (i ==ax and j == ay) else print("%-5d" % (-1), end='')
    print()
