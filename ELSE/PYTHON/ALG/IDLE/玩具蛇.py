#玩具蛇dfs
flags=[(0,1),(1,0),(0,-1),(-1,0)]
def dfs(lenth,x,y):
    if lenth==16:
        global cnt
        cnt+=1
    for d in flags:
        nx,ny=d[0]+x,d[1]+y
        if nx>=0 and nx<4 and ny>=0 and ny<4 and seen[nx][ny]==0:
            seen[nx][ny]=1
            dfs(lenth+1,nx,ny)
            seen[nx][ny]=0
cnt=0
seen=[[0]*4 for _ in range(4)]
for i in range(4):
    for j in range(4):
        
        seen[i][j]=1
        dfs(1,i,j)
        seen[i][j]=0
print(cnt)
