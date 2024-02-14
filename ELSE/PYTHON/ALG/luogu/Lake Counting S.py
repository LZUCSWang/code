"""
10 12
W........WW.
.WWW.....WWW
....WW...WW.
.........WW.
.........W..
..W......W..
.W.W.....WW.
W.W.W.....W.
.W.W......W.
..W.......W.
"""
from collections import deque
n, m = map(int, input().split())
data = [input() for _ in range(n)]
# print(data)
flags = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
seen = [[0]*m for _ in range(n)]
# print(seen)
cnt = 0


def bfs(x, y):
    queue = deque([(x, y)])
    # print(queue)
    global seen
    while len(queue) > 0:
        item = queue.popleft()
        for d in flags:
            nx, ny = d[0]+item[0], d[1]+item[1]
            if nx >= 0 and nx < n and ny >= 0 and ny < m and data[nx][ny] == 'W' and seen[nx][ny] == 0:
                seen[nx][ny] = 1
                queue.append((nx, ny))


for i in range(n):
    for j in range(m):
            if data[i][j] == 'W' and seen[i][j] == 0:
                seen[i][j] = 1
                bfs(i, j)
                cnt += 1
print(cnt)
