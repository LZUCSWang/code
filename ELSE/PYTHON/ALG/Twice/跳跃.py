"""3 5
-4 -5 -10 -3 1
7 5 -9 3 -10
10 -2 6 -10 -4"""
n, m = map(int, input().split())
data = [list(map(int, input().split())) for _ in range(n)]
dp = [[0]*m for _ in range(n)]


def dfs(x, y):
    if x < 0 or y < 0:
        return -float('inf')
    if x == 0 and y == 0:
        return data[0][0]
    before = max(dfs(x-1, y), dfs(x-2, y), dfs(x-3, y), dfs(x-1, y-1),
                 dfs(x-2, y-2), dfs(x-1, y-2), dfs(x, y-1), dfs(x, y-2), dfs(x, y-3))
    return before+data[x][y]


print(dfs(n-1, m-1))
