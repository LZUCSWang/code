n = int(input())
tdata = list(map(int, input().split()))
data = [0]+tdata+tdata
sum = [0]*(2*n+1)
maxdp, mindp = [[0]*(2*n+1) for _ in range(2*n+1)], [[0]*(2*n+1)
                                                     for _ in range(2*n+1)]
for i in range(1, 2*n+1):
    sum[i] = sum[i-1]+data[i]
for jiange in range(2, n+1):
    for l in range(1, 2*n-jiange+2):
        r = l+jiange-1
        mindp[l][r] = float('inf')
        for k in range(l, r):
            temp = sum[r]-sum[l-1]
            maxdp[l][r] = max(maxdp[l][r], maxdp[l][k]+maxdp[k+1][r]+temp)
            mindp[l][r] = min(mindp[l][r], mindp[l][k]+mindp[k+1][r]+temp)
print(mindp[n][2*n-1])
print(maxdp[n][n*2-1])
