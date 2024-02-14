import sys
from collections import deque
n, m = map(int, input().split())
data = [list(input()) for _ in range(n)]
cnt = 0
seen = [[0]*m for _ in range(n)]
flags = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def bfs(x, y):
    queue = deque([(x, y)])
    while len(queue):
        item = queue.popleft()
        for d in flags:
            nx, ny = item[0]+d[0], item[1]+d[1]
            if nx >= 0 and nx < n and ny >= 0 and ny < m and seen[nx][ny] == 0 and data[nx][ny] == '#':
                seen[nx][ny] = 1
                queue.append((nx, ny))


for i in range(n):
    for j in range(m):
        if seen[i][j] == 0 and data[i][j] == '#':
            seen[i][j] = 1
            bfs(i, j)
            cnt += 1
# for i in range(n):
#     print(seen[i])
for i in range(n-1):
    for j in range(m-1):
        if (data[i][j]+data[i+1][j]+data[i][j+1]+data[i+1][j+1]).count('.') == 1:
            print("Bad placement.")
            sys.exit()
print("There are %d ships." % cnt)
