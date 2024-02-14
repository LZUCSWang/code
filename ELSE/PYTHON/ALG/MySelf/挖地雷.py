"""5
10 8 4 7 6
1 1 1 0
0 0 0
1 1
1"""
import sys
n = int(input())

graph = {}
dp = [0]*(n+1)
globalmax = 0
seen = [0]*(n+1)
sm = 0
path = [0]*(n+1)
data = [0]+list(map(int, sys.stdin.readline().split()))


def check(x):
    for i in graph[x]:
        if seen[i] == 0:
            return True
    return False


for i in range(1, n):
    graph[i] = []
    temp = list(map(int, sys.stdin.readline().split()))
    for j in range(n-i):
        if temp[j] == 1:
            graph[i].append(j+i+1)
graph[n] = []
cnt = [0]*(n+1)


def dfs(x, step, sm):
    global globalmax
    if not check(x):
        if globalmax < sm:
            globalmax = sm
            for i in range(1, n+1):
                cnt[i] = path[i]
    for i in graph[x]:
        if seen[i] == 0:
            seen[i] = 1
            path[step+1] = i
            dfs(i, step+1, sm+data[i])
            seen[i] = 0


for i in range(1, n+1):
    seen[i] = 1
    path = [0]*(n+1)
    path[1] = i
    dfs(i, 1, sm+data[i])
    seen[i] = 0
for i in range(1, n+1):
    if cnt[i] != 0:
        print(cnt[i], end=' ')
print()
print(globalmax)
