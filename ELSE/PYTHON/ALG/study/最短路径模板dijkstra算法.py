cost={}
parent={}
graph={}
visited=[]
def lcm(datas,b):
    s=datas*b
    while b:
        datas,b=b,datas%b
    return s//datas
for i in range(1,2022):
    graph[i]={}
    if i<=2000:
        for j in range(i+1,i+22):
            graph[i][j]=lcm(i,j)
    else:
        for j in range(i+1,2022):
            graph[i][j]=lcm(i,j)
for i in range(2,2022):
    if i<23:
        cost[i]=i
    else:
        cost[i]=float('inf')
for i in range(2,2022):
    if i<23:
        parent[i]=1
    else:
        parent[i]=None
def getmin(cost):
    mc, mcn = float('inf'), None
    for i in cost.keys():
        if i not in visited and cost[i] < mc:
            mc = cost[i]
            mcn = i
    return mcn


node = getmin(cost)
while node:
    neibor = graph[node]
    nowcost = cost[node]
    for i in neibor.keys():
        if nowcost+neibor[i] < cost[i]:
            cost[i] = nowcost+neibor[i]
    visited.append(node)
    node = getmin(cost)
print(cost[2021])

# print(cost)
