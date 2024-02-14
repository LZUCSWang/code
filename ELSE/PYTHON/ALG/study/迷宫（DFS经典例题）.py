N,M,T=map(int,input().split())
x1,y1,x2,y2=map(int,input().split())
start=(x1,y1)
end=(x2,y2)
trap=[]
seen=[[0]*(N+1) for _ in range(M+1)]
seen[start[0]][start[1]]=1
flags=[(0,-1),(0,1),(1,0),(-1,0)]
for i in range(T):
    x1,y1=map(int,input().split())
    trap.append((x1,y1))
def check(x,y):
    if (x,y) in trap or x>M or x<=0 or y>N or y<=0:
        return 0
    return 1
cnt=0
def dfs(x,y):
    global cnt
    if x>M or x<=0 or y>N or y<=0:
        return 0
    if (x,y)==end:
        cnt+=1
        return 1
    for i in flags:
        nx,ny=x+i[0],y+i[1]
        if check(nx,ny)==1 and seen[nx][ny]==0:
            seen[nx][ny]=1
            dfs(nx,ny)
            seen[nx][ny]=0
dfs(start[0],start[1])
print(cnt)