from collections import deque


def dfs(x, y):  # 表示x,y的属性
    f1 = True
    for d in flags:
        nx, ny = x+d[0], y+d[1]
        if nx >= 0 and nx < n and ny >= 0 and ny < m and data[nx][ny] == '1':
            flag[x][y] = 2
            f1 = False
            break
    if f1:
        flag[x][y] = 1


flags = ((1, 0), (0, 1), (0, -1), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1))
n, m = map(int, input().split())
data = [input().split() for _ in range(n)]
flag = [[0]*m for _ in range(n)]
for i in range(n):
    for j in range(m):
        if data[i][j] == '0':
            dfs(i, j)
cnt = 0


def bfs(i, j):
    queue = deque([(i, j)])
    while len(queue):
        item = queue.popleft()
        x, y = item[0], item[1]
        for d in flags:
            nx, ny = x+d[0], y+d[1]
            if nx >= 0 and nx < n and ny >= 0 and ny < m and data[nx][ny] != 0 and flag[nx][ny]==1:
                data[nx][ny] = 0
                queue.append((nx, ny))

# for i in range(n):
#     print(flag[i])
for i in range(n):
    for j in range(m):
        if flag[i][j] == 2:
            f1 = True
            for d in flags:
                nx, ny = i+d[0], j+d[1]
                if nx >= 0 and nx < n and ny >= 0 and ny < m and flag[nx][ny] == 1:
                    f1 = False
                    break
            if f1:
                cnt += 1
                # print(i,j)
        if flag[i][j] == 1 and data[i][j] != 0:
            cnt += 1
            # print(i,j)
            data[i][j] = 0
            bfs(i, j)
print(cnt)
# for i in range(n):
#     print(data[i])
