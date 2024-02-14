"""
5 10
2 3 5
1 5 5
3 5 6
1 2 8
1 3 8
5 3 4
4 1 8
4 5 3
3 5 6
5 4 2
"""
n, m = map(int, input().split())
graph1, graph2 = {}, {}
for i in range(1, n+1):
    graph1[i] = {}
    graph2[i] = {}
for i in range(m):
    datas, b, c = map(int, input().split())
    if b in graph1[datas].keys():
        graph1[datas][b] = min(graph1[datas][b], c)
    else:
        graph1[datas][b] = c
    if datas in graph2[datas].keys():
        graph2[b][datas] = min(graph2[b][datas], c)
    else:
        graph2[b][datas] = c


def getmin(cost, seen):
    mc, mcn = float('inf'), None
    for i in cost.keys():
        if i not in seen and cost[i] < mc:
            mc = cost[i]
            mcn = i

    return mcn


def dijis(graph, cost):
    cost[1] = 0
    seen = []
    node = getmin(cost, seen)
    while node:
        neibor, nowcost = graph[node], cost[node]
        for i in neibor.keys():
            temp = nowcost+neibor[i]
            if temp < cost[i]:
                cost[i] = temp
        seen.append(node)
        node = getmin(cost, seen)


cost1, cost2 = {}, {}
for i in range(1, n+1):
    cost1[i] = cost2[i] = float('inf')
dijis(graph1, cost1)
dijis(graph2, cost2)
# print(cost2)
# print(cost1)
cnt = 0
for i in range(1, n+1):
    cnt += cost1[i]+cost2[i]
print(cnt)
# print(cost[])
