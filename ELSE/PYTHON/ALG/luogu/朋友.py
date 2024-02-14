n,m,p,q=map(int,input().split())
prea,preb=[i for i in range(0,n+1)],[i for i in range(0,m+1)]
#print(prea,preb)
def find(x,last):
    if x!=last[x]:
        last[x]=find(last[x],last)
    return last[x]
def deal(last,n):
    for i in range(n):
        datas,b=map(int,input().split())
        datas,b=abs(datas),abs(b)
        if datas==b:
            continue
        at,bt=find(datas,last),find(b,last)
        if at!=bt:
            minab=min(at,bt)
            last[at]=last[bt]=minab
deal(prea,p)
deal(preb,q)
cnt=0
for i in range(1,min(n,m)+1):
    if prea[i]==1 and preb[i]==1:
        cnt+=1
print(cnt)

    