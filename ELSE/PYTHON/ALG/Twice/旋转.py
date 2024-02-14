n, m = map(int, input().split())
data = [list(map(int, input().split())) for _ in range(n)]
out = [[0]*n for _ in range(m)]
p, q = 0, n-1
for i in range(n):
    for j in range(m):
        out[p][q] = data[i][j]
        if j == m-1:
            p = 0
            q -= 1
        else:
            p += 1
for i in range(m):
    print(*out[i])
