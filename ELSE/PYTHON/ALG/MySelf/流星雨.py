import sys
n = int(input())
place = [[-1]*305 for _ in range(305)]
flags = [(0, 0), (0, 1), (1, 0), (0, -1), (-1, 0)]
for i in range(n):
    datas, b, t = map(int, input().split())
    for j in flags:
        nnx, nny = datas+j[0], b+j[1]
        if nnx >= 0 and nny >= 0 and (place[nnx][nny] == -1 or place[nnx][nny] > t):
            place[nnx][nny] = t

queue = []
seen = [[0]*305 for _ in range(305)]
queue.append((0, 0, 0))
seen[0][0] = 1
while len(queue) > 0:
    item = queue.pop(0)
    x, y, t = item[0], item[1], item[2]
    if place[x][y] == -1:
        print(t)
        sys.exit()
    for d in range(1, 5):
        nx, ny = x+flags[d][0], y+flags[d][1]
        if nx >= 0 and ny >= 0 and seen[nx][ny] == 0 and (t+1 < place[nx][ny] or place[nx][ny] == -1):
            seen[nx][ny] = 1
            queue.append((nx, ny, t+1))
print(-1)
