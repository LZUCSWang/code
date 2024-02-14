n,m=map(int,input().split())
last=[i for i in range(n+1)]
def find(x):
    if last[x]!=x:
        last[x]=find(last[x])
    return last[x]
def union(x,y):
    nx,ny=find(x),find(y)
    if nx!=ny:
        last[nx]=ny
for i in range(m):
    datas,b,c=map(int,input().split())
    if datas==1:
        union(b,c)
    else:
        print("Y") if find(b)==find(c) else print("N")