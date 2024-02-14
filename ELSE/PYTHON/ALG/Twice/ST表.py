import math
dp = [[0]*40 for _ in range(int(5e5))]


def init():
    global dp, n
    loog = int(math.log2(n))
    for i in range(1, loog+1):
        for j in range(1, n-(1 << i)+2):
            dp[j][i] = max(dp[j][i-1], dp[j+(1 << (i-1))][i-1])


def got(L, R):
    loog = int(math.log2(R-L+1))
    return max(dp[L][loog], dp[R-(1 << loog)+1][loog])


n, m = map(int, input().split())
data = [0]+list(map(int, input().split()))
for i in range(1, n+1):
    dp[i][0] = data[i]
init()
for i in range(m):
    L, R = map(int, input().split())
    print(got(L, R))
