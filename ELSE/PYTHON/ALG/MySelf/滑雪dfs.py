import sys
row, col = map(int, input().split())
data = [list(map(int, sys.stdin.readline().split())) for _ in range(row)]
dp = [[0]*col for _ in range(row)]
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def dfs(x, y):
    if dp[x][y]:
        return dp[x][y]
    dp[x][y] = 1
    for d in flags:
        nx, ny = x+d[0], y+d[1]
        if nx >= 0 and nx < row and ny >= 0 and ny < col and data[nx][ny] < data[x][y]:
            dfs(nx, ny)
            dp[x][y] = max(dp[x][y], dp[nx][ny]+1)
    return dp[x][y]

cnt=0
for i in range(row):
    for j in range(col):
        cnt=max(cnt,dfs(i, j))
print(cnt)
