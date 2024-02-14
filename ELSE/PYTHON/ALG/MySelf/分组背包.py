m, n = map(int, input().split())
z = [0]*10000
dp = [0]*(m+1)
w, v = [0]*(n+1), [0]*(n+1)
bk = [[0]*100 for _ in range(100)]
zushu = 0
for i in range(1, n+1):
    datas, b, c = map(int, input().split())
    zushu = max(zushu, c)
    w[i], v[i] = datas, b
    z[c] += 1
    bk[c][z[c]] = i#第c组的第z[c]个物体的总下标
for i in range(1, zushu+1):
    for j in range(m, -1, -1):
        for k in range(1, z[i]+1):
            px = bk[i][k]
            if w[px] <= j:
                dp[j] = max(dp[j], dp[j-w[px]]+v[px])
print(dp[m])
