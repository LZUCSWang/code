"""
5 5
1 2 3 4 5
1 1 
1 2 
1 3
3 4
2 5
"""


import sys
import math
n, m = map(int, input().split())
data = [0]+list(map(int, input().split()))
# dp[i][j] 以i为起点，宽度为1<<j 的区间的最大值
maxwide = int(math.log2(n))
dp = [[0]*(maxwide+1) for _ in range(n+1)]
for i in range(1, n+1):
    dp[i][0] = data[i]
for j in range(1, maxwide+1):
    for i in range(1, n-(1 << j)+2):
        dp[i][j] = max(dp[i][j-1], dp[i+(1 << j-1)][j-1])
# sys.exit()


def find(left, right):
    if left == right:
        return data[left]
    lenth = right-left+1
    kk = int(math.log2(lenth))
    # if dp[left][kk] != 0:
    #     return dp[left][kk]
    return max(dp[left][kk], dp[right-(1 << kk)+1][kk])


for i in range(m):
    left, right = map(int, input().split())
    print(find(left, right))
