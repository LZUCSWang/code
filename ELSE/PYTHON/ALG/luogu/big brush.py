n, m = map(int, input().split())
data = [[0]*(m+1)]
for i in range(n):
    data.append([0]+list(map(int, input().split())))


def getmost(i, j):
    return max(data[i][j], data[i+1][j], data[i][j+1], data[i+1][j+1])


def con(datas, i, j):
    if (datas == data[i][j] or data[i][j] == -1) and (datas == data[i+1][j] or data[i+1][j] == -1) and (datas == data[i][j+1] or data[i][j+1] == -1) and (datas == data[i+1][j+1] or data[i+1][j+1] == -1):
        return 1
    return 0


def judge(i, j):
    m = max(data[i][j], data[i+1][j], data[i][j+1], data[i+1][j+1])
    if con(m, i, j):
        return 1
    return 0


queue = []
for i in range(1, n):
    for j in range(1, m):
        if (judge(i, j)):
            queue.append((i, j, data[i][j]))
cnt = []
while len(queue) > 0:
    item = queue.pop(0)
    x, y = item[0], item[1]
    if getmost(x, y) == -1:
        continue
    cnt.append(item)
    data[x][y] = data[x+1][y] = data[x][y+1] = data[x+1][y+1] = -1
    for i in range(-1, 2):
        for j in range(-1, 2):
            if i == 0 and j == 0:
                continue
            nx, ny = x+i, y+j
            if nx == 0 or ny == 0 or nx == n or ny == m or getmost(nx, ny) == -1 or judge(nx, ny) == 0 or (nx, ny, getmost(nx, ny)) in queue:
                continue
            queue.append((nx, ny, getmost(nx, ny)))
print(len(cnt))
for i in range(len(cnt)-1, -1, -1):
    print(cnt[i][0], cnt[i][1], cnt[i][2])
