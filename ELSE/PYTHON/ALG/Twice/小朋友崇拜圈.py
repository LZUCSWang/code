n = int(input())
seen = [0]*(n+1)
data = [0]+list(map(int, input().split()))


def dfs(x, t):
    if seen[x] == 2:
        global maxt
        maxt = max(t, maxt)
        return
    if seen[x] == 1:
        return
    seen[x] = 1
    dfs(data[x], t+1)
    seen[x] = 0


maxt = 0
for i in range(1, n+1):
    seen[i] = 2
    dfs(data[i], 1)
    seen[i] = 0
print(maxt)
