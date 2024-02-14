def minFallingPathSum(self, grid) -> int:
    import copy
    if not grid:
        return 0
    m, n = len(grid), len(grid[0])
    dp = copy.deepcopy(grid[0])
    for i in range(1, m):
        temp = [0]*n
        for j in range(n):

            if j == 0:
                temp[j] = min(dp[1:])+grid[i][j]
            elif j == n - 1:
                temp[j] = min(dp[:j])+grid[i][j]
            else:
                temp[j] = min(min(dp[:j]),min(dp[j+1:]))+grid[i][j]
        dp = temp
    return min(dp)


print(minFallingPathSum(0, [[-73, 61, 43, -48, -36], [3, 30, 27, 57, 10],
      [96, -76, 84, 59, -15], [5, -49, 76, 31, -7], [97, 91, 61, -46, 67]]))
# [[-73, 61, 43, -48, -36],
#  [3, 30, 27, 57, 10],
#  [96, -76, 84, 59, -15],
#  [5, -49, 76, 31, -7],
#  [97, 91, 61, -46, 67]]
