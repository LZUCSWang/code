#最短路径-路径
def lcm(datas,b):
    s=datas*b
    while b:
        datas,b=b,datas%b
    return s//datas
 
graph={}#生成图
for i in range(1,2022):
    graph[i]={}
    if i<=2000:
        for j in range(i+1,i+22):
            graph[i][j]=lcm(i,j)
    else:
        for j in range(i+1,2022):
            graph[i][j]=lcm(i,j)
graph[2021]={}
cost={}#键是从1节点到键节点的键，值是1节点到该键的最小cost
for i in graph[1]:#节点1到23节点的路径cost是已知的对应第一步
    cost[i]=graph[1][i]
for i in range(23,2022):
    cost[i]=float("inf")#节点1到23以后的都暂时不知道，定义为最大
print(cost)
parent={}#键是子节点，值是父节点
for i in range(2,23):#1到23节点的父节点是已知的，都是1开始的
    parent[i]=1
for i in range(23,2022):#23以后的节点的父节点暂时未知
    parent[i]=None
v=[]
def mc(cost):
    mc,mcn=float("inf"),None
    for node in cost.keys():
        costs=cost[node]#
        if costs<mc and node not in v:
            mc,mcn=costs,node
    return mcn
node=mc(cost)
while node:
    costs=cost[node]
    nb=graph[node]
    for i in nb.keys():
        new=costs+nb[i]
        if new<cost[i]:
            cost[i]=new
            parent[i]=node
    v.append(node)
    node=mc(cost)
print(cost[2021])#10266837