import os
import sys
graph = {}
n, m = map(int, input().split())
for i in range(m):
    datas, b, c = map(int, input().split())
    try:
        graph[datas][b] = c
    except:
        graph[datas] = {}
        graph[datas][b] = c
    try:
        graph[b][datas] = c
    except:
        graph[b] = {}
        graph[b][datas] = c
cost = [0, 0]+[float('inf')]*(n-1)
seen = [0]*(n+1)


def findcost(cost):
    mc, mcn = float("inf"), None
    for i in range(1, n+1):
        if cost[i] < mc and seen[i] == 0:
            mc = cost[i]
            mcn = i
    return mcn


node = findcost(cost)
while node:
    hacost = cost[node]
    neighbor = graph[node]
    for i in neighbor.keys():
        temp = neighbor[i]+hacost
        if temp < cost[i]:
            cost[i] = temp
    seen[node] = 1
    node = findcost(cost)
print(*(cost[1:]))
# 请在此输入您的代码
