n = int(input())
dp = [float('inf')]*(n+1)
data = {}
dp[1] = 0
for i in range(1, n):
    temp = [0]+list(map(int, input().split()))
    for j in range(i+1, n+1):
        data[(i, j)] = temp[j-i]
for i in range(1, n+1):
    for j in range(1, i):
        dp[i] = min(dp[i], dp[j]+data[(j, i)])
print(dp[-1])
