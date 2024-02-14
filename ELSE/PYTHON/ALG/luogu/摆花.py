mo = 1000007
n, m = map(int, input().split())
data = [0]+list(map(int, input().split()))

# 记忆化搜索
"""
jiyi=[[0]*(m+1) for _ in range(n+1)]
def dfs(num, index):
    if index == m:
        return 1
    if num > n or index > m:
        return 0
    if jiyi[num][index]:
        return jiyi[num][index]
    cnt = 0
    for times in range(data[num]+1):
        cnt = (cnt+dfs(num+1, index+times)) % mo
    jiyi[num][index]=cnt
    return cnt
print(dfs(1,0))"""
# dp
dp = [[0]*(m+1) for _ in range(n+1)]
dp[0][0] = 1
for i in range(1, n+1):
    for j in range(m+1):
        for k in range(min(data[i], j)+1):
            dp[i][j] = (dp[i][j]+dp[i-1][j-k]) % mo
print(dp[n][m])
