n,m,p=map(int,input().split())
per=[i for i in range(n+1)]

def find_root(x):
    if per[x]!=x:
        per[x]=find_root(x)
    return per[x]
def union(x,y):
    x_root,y_root=find_root(x),find_root(y)
    if x_root!=y_root:
        per[x_root]=y_root
for i in range(m):
    datas,b=map(int,input().split())
    union(datas,b)
for i in range(p):
    datas,b=map(int,input().split())
    if find_root(x)==find_root(y):
        print("Yes")
    else:
        print("No")