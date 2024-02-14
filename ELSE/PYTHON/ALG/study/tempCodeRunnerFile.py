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
def most_c(cost):
    mostchecp,mostchecpnode=float('inf'),None
    for i in cost.keys():
        tempchecp=cost[i]
        if tempchecp<mostchecp and i not in visited:
            mostchecp =tempchecp
            mostchecpnode=i
    return mostchecpnode
node=most_c(cost)
while node:
    costs=cost[node]
    neighbor=graph[node]
    for i in neighbor.keys():
        tempcost=costs+neighbor[i]
        if tempcost<cost[i]:
            cost[i]=tempcost
            parent[i]=node
    visited.append(node)
    node=most_c(cost)
print(cost[2021])