n=int(input())
data=list(map(int,input().split()))
last=[i for i in range(10000000)]
def find(x):
    if last[x]!=x:
        last[x]=find(last[x])
    return last[x]

def union(x,y):
    rx,ry=find(x),find(y)
    if rx!=ry:
        second=max(rx,ry)
        first=max(rx,ry)
        last[first]=second

