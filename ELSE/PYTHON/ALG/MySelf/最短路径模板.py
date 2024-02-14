"""
4 5 0 3
20 30 40 10
0 1 1
1 3 2
0 3 3
0 2 2
2 3 2
"""
n,m,s,e=map(int,input().split())
teamdata=list(map(int,input().split()))
st=[0]*n
st[s]=teamdata[s]
sel=[[float("inf")]* n for  _ in range(n)]
dis=[float('inf')]*n
dis[s]=0
seen=[0]*n
parent={}
num=[0]*n
num[s]=1
for i in range(n):
    sel[i][i]=0
for i in range(m):
    datas,b,c=map(int,input().split())
    sel[datas][b]=c 
    sel[b][datas]=c
while True:    
    mc,mcn=float('inf'),None
    for i in range(n):
        if seen[i]==0 and dis[i]<mc:
            mcn=i
            mc=dis[i]
    if mcn==None:
        break
    seen[mcn]=1
    for i in range(n):
        if seen[i]==0 and mc+sel[mcn][i]<dis[i]:
            dis[i]=mc+sel[mcn][i]
            st[i]=st[mcn]+teamdata[i]
            parent[i]=mcn
            num[i]=num[mcn]
        elif seen[i]==0 and mc+sel[mcn][i]==dis[i]:
            if st[i]<st[mcn]+teamdata[i]:
                parent[i]=mcn
                st[i]=st[mcn]+teamdata[i]
            num[i]+=num[mcn]
print(num[e],st[e])
import sys
cnt=[e]
while True:
    try:
        cnt.append(parent[e])
        e=parent[e]
    except:
        print(' '.join(map(str,cnt)))
        sys.exit()
