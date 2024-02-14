m, n = map(int, input().split())


def deal(x, y):
    global time,crow,row
    if x-1 >= 0:
        row[x][y] += crow[x-1][y]
        time += 1
    if x+1 < m:
        row[x][y] += crow[x+1][y]
        time += 1
    if y-1 >= 0:
        row[x][y] += crow[x][y-1]
        time += 1
    if y+1 < n:
        row[x][y] += crow[x][y+1]
        time += 1
    if x-1 >= 0 and y-1 >= 0:
        row[x][y] += crow[x-1][y-1]
        time += 1
    if x-1 >= 0 and y+1 < n:
        row[x][y] += crow[x-1][y+1]
        time += 1
    if x+1 < m and y-1 >= 0:
        row[x][y] += crow[x+1][y-1]
        time += 1
    if x+1 < m and y+1 < n:
        row[x][y] += crow[x+1][y+1]
        time += 1
    row[x][y] //= (time+1)


row = []
for i in range(m):
    row.append(list(map(int, input().split())))
crow = [[0]*len(row[0]) for _ in range(m)]
for i in range(m):
    for j in range(n):
        crow[i][j]=row[i][j]
for i in range(m):
    for j in range(n):
        time=0
        deal(i, j)
for i in range(m):
    print(' '.join(map(str,row[i])))
# 请在此输入您的代码
