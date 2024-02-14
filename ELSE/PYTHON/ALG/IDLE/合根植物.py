#合根植物
n,m=map(int,input().split())
k=int(input())
def find(x):
    if last[x]!=x:
        last[x]=find(last[x])
    return last[x]
def union(x,y):
    rx,ry=find(x),find(y)
    if rx!=ry:
        last[rx]=ry
last=[i for i in range(n*m+1)]
for i in range(k):
    datas,b=map(int,input().split())
    if find(datas)!=find(b):
        union(datas,b)
cnt=[0]*(n*m+1)
cnt=0
for i in range(1,n*m+1):
    ppp=find(i)
    if cnt[ppp]>=1:
        continue
    cnt[ppp]+=1
    if cnt[ppp]>=1:
        cnt+=1
print(cnt)
