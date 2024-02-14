def dfs(i, x, y):
    global cnt
    if i >= n:
        if x == 1 and y == 0:
            return
        cnt = min(abs(x-y), cnt)
        return
    dfs(i+1, x*data[i][0], y+data[i][1])
    dfs(i+1, x, y)


n = int(input())
cnt = float('inf')
data = [tuple(map(int, input().split())) for _ in range(n)]
dfs(0, 1, 0)
print(cnt)
