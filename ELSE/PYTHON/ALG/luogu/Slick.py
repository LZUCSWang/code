from collections import deque
n, m = map(int, input().split())
data = [input().split() for _ in range(n)]
seen = [[False]*m for _ in range(n)]
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def bfs(i, j):
    queue = deque([(i, j)])
    global cnt
    while len(queue):
        item = queue.popleft()
        cnt += 1
        x, y = item[0], item[1]
        for d in flags:
            nx, ny = x+d[0], y+d[1]
            if nx >= 0 and ny >= 0 and nx < n and ny < m and not seen[nx][ny] and data[nx][ny] == '1':
                queue.append((nx, ny))
                seen[nx][ny] = True


cntlist = [0]*100000
cnt = 0
for i in range(n):
    for j in range(m):
        if seen[i][j] == False and data[i][j] == '1':
            cnt = 0
            seen[i][j] = True
            bfs(i, j)
            cntlist[cnt] += 1
            cnt += 1
print(cnt)
for i in range(1, len(cntlist)):
    if cntlist[i]:
        print(i, cntlist[i])
