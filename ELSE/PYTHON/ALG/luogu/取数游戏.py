def dfs(x, y, cnt):
    # choice
    if y == m+1:
        dfs(x+1, 0, cnt)
        return
    if x == n+1:
        global mt
        mt = max(cnt, mt)
        # print(cnt,x,y)
        # print(1)
        return
    dfs(x, y+1, cnt)
    if seen[x][y] == 0:
        for d in flags:
            seen[x+d[0]][y+d[1]] += 1
        # if x==2 and y==1:
        #     datas=1
        dfs(x, y+1, cnt+data[x][y])

        for d in flags:
            seen[x+d[0]][y+d[1]] -= 1


n = int(input())
flags = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
for i in range(n):
    mt = 0
    n, m = map(int, input().split())
    seen = [[0]*(m+2) for _ in range(n+2)]
    data = [[0]*(m+1)]+[[0]+list(map(int, input().split())) for _ in range(n)]
    # print(data)
    dfs(1, 1, 0)
    print(mt)
