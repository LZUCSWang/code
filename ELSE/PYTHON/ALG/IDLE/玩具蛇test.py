#玩具蛇dfs
flags=[(0,1),(1,0),(0,-1),(-1,0)]
def dfs(lenth,x,y):
    if lenth==n*n:
        global cnt
        cnt+=1
    for d in flags:
        nx,ny=d[0]+x,d[1]+y
        if nx>=0 and nx<2 and ny>=0 and ny<n and seen[nx][ny]==0:
            seen[nx][ny]=1
            dfs(lenth+1,nx,ny)
            seen[nx][ny]=0
cnt=0
n=2
seen=[[0]*n for _ in range(n)]
for i in range(n):
    for j in range(n):
        
        seen[i][j]=1
        dfs(1,i,j)
        seen[i][j]=0
print(cnt)
