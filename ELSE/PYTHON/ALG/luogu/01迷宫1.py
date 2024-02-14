from collections import deque
n, m = map(int, input().split())
data = [input() for _ in range(n)]
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]
seen = [[0]*n for _ in range(n)]


def bfs(i, j):
    queue = deque([(i, j)])
    global cnt
    while len(queue):
        # print('#')
        cnt += 1
        item = queue.popleft()
        x, y = item[0], item[1]
        for d in flags:
            nx, ny = d[0]+x, d[1]+y
            if nx >= 0 and nx < n and ny >= 0 and ny < n and data[nx][ny] != data[x][y] and seen[nx][ny] == 0:
                queue.append((nx, ny))
                seen[nx][ny] = (i,j)


cnt = {}
for i in range(n):
    for j in range(n):
        if seen[i][j] == 0:
            seen[i][j] = (i,j)
            cnt = 0
            bfs(i, j)
            cnt[(i, j)] = cnt
# print(last)
for i in range(m):
    datas, b = map(int, input().split())
    datas -= 1
    b -= 1
    print(cnt[seen[datas][b]])
# print(cnt)