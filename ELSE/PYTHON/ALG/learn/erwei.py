m,n=3,4
f = [[1] * n] + [[1] + [0] * (n - 1) for _ in range(m - 1)]
for i in range(1,m):
    for j in range(1,n):
        f[i][j]=f[i][j-1]+f[i-1][j]
print(f[m-1][n-1])