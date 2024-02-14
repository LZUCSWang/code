flags = [(1, 2), (2, 2), (2, 1), (-1, 2), (-2, 1), (-2, 2),
        (1, -2), (2, -1), (2, -2), (-1, -2), (-2, -1), (-2, -2)]

for i in range(2):
    x, y = map(int, input().split())
    seen = [[0]*(100) for _ in range(100)]
    queue = []
    queue.append((x, y, 0))
    seen[x][y]=1
    while len(queue) > 0:
        item = queue.pop(0)
        xi, yi, t = item[0], item[1], item[2]
        if xi == 1 and yi == 1:
            print(t)
            break
        for d in flags:
            nx, ny = xi+d[0], yi+d[1]
            if nx > 0 and ny > 0 and nx <= 100 and ny <= 100 and seen[nx][ny] == 0:
                if nx==1 and ny==1:
                    print(t+1)
                    queue=[]
                    break
                seen[nx][ny] = 1
                queue.append((nx, ny, t+1))
