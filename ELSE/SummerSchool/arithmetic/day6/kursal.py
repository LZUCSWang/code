n, m = map(int, input().split())
edges = []
for i in range(m):
    edges.append(list(map(int, input().split())))
edges.sort(key=lambda x: x[2])
parent=[i for i in range(n+1)]
def find(x):
    if x != parent[x]:
        parent[x] = find(parent[x])
    return parent[x]
def union(x,y):
    x ,y = find(x),find(y)
    if x != y:
        parent[x] = y
ans=0
cnt=0
for i in range(m):
    if (find(edges[i][0])!=find(edges[i][1])):
        ans+=edges[i][2]
        cnt+=1
        union(edges[i][0],edges[i][1])
    if cnt==n-1:
        break
print(ans)