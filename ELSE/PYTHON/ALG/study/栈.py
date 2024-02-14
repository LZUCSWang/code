n = int(input())
dp = [[0]*(n+1) for _ in range(n+1)]


def dfs(i, j):
    if dp[i][j] != 0:
        return dp[i][j]
    if i == 0:
        return 1
    if j > 0:
        dp[i][j] += dfs(i, j-1)
    dp[i][j] += dfs(i-1, j+1)
    return dp[i][j]


print(dfs(n, 0))
