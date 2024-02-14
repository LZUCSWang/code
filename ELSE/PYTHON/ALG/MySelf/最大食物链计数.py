import sys
n, m = map(int, sys.stdin.readline().split())
eat = [[] for _ in range(n+1)]
prod = [0]*(n+1)
seen = [0]*(n+1)
cnt = 0
for i in range(m):
    be, e = map(int, sys.stdin.readline().split())
    prod[e] = 1
    eat[be].append(e)
dp=[0]*(n+1)

def dfs(x):
    global cnt
    if eat[x] == []:
        cnt += 1
        return
    
    for i in eat[x]:
        if seen[x] == 0:
            seen[x] = 1
            dfs(i)
            seen[x] = 0


for i in range(1, n+1):
    if prod[i] == 0:
        dfs(i)
print(cnt)
