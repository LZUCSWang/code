import sys
import math
n, m = map(int, input().split())
data = [0]+list(map(int, input().split()))
loglenth = int(math.log2(m))
dp = [[float('inf')]*(loglenth+1) for _ in range(n+1)]
for i in range(1,n+1):
    dp[i][0] = data[i]

for j in range(1, loglenth+1):
    for i in range(1, n-(1 << j-1)+1):
        dp[i][j] = min(dp[i][j-1], dp[i+(1 << (j-1))][j-1])


def search(left, right):
    lenth = right-left+1
    k = int(math.log2(lenth))
    if left == right:
        return data[left]
    return min(dp[left][k], dp[right-(1 << k)+1][k])


for i in range(1, n-m+2):
    print(search(i, i+m-1))

# sys.exit()