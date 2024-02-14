parent=[i for i in range(2022)]
def find_parent(x):
    if x!=parent[x]:
        parent[x]=find_parent(parent[x])
    return parent[x]
def union(x,y):
    x_root,y_root=find_parent(x),find_parent(y)
    if x_root!=y_root:
        parent[x_root]=y_root
def cost(x,y):
    datas = '0'*(4-len(str(x)))+str(x)
    b = '0'*(4-len(str(y)))+str(y)
    s = 0
    for i in range(4):
        if datas[i] != b[i]:
            s += int(datas[i])+int(b[i])
    return s
edge=[(i,j,cost(i,j)) for i in range(1,2022) for j in range(1,2022)]
edge.sort(key=lambda x:x[2])
j=0
cnt=0
for i in edge:
    if find_parent(i[0])!=find_parent(i[1]) and j<2020:
        cnt+=i[2]
        j+=1
        union(i[0],i[1])
print(cnt)