import sys
n, m, s, e= map(int, input().split())
if s==e:
    print(0)
    exit()
graph = {}
inf = 2**31-1
cost = [inf]*(n+1)
cost[s] = 0
seen = [False]*(n+1)
seen[s]=True
graph = {i: [] for i in range(1, n+1)}
for i in range(m):
    datas, b, c = map(int, sys.stdin.readline().split())
    graph[datas].append((b, c))
for item in graph[s]:
    cost[item[0]] = item[1]


def mostchecp(cost):
    mc, mcn = inf, None
    for i in range(n):
        if seen[i]==False and cost[i] < mc:
            mc = cost[i]
            mcn = i
    return mcn


node = mostchecp(cost)
while node:
    co = cost[node]
    neighbor = graph[node]
    for item in neighbor:
        tempcost = item[1]+co
        if tempcost < cost[item[0]]:
            cost[item[0]] = tempcost
    seen[node]=True
    node = mostchecp(cost)
print(cost[e])
