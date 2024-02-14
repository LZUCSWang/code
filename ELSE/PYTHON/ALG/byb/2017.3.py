cnt=0
flag=[[0]*7 for _ in range(7)]
print(flag)
def dfs(x,y):
    if x==0 or x==6 or y==0 or y==6:
        global cnt
        cnt+=1
        return
    flag[x][y]=1
    flag[6-x][6-y]=1
    for i in flag:
        nx=x+i[0]
        ny=y+i[1]
        if nx<0 or ny<0 or nx>6 or ny>6:
            continue
        if(flag[nx][ny]==0):
            dfs(nx,ny)
    flag[x][y]=0
    flag[6-x][6-y]=0
flag=[[0,1],[0,-1],[-1,0],[1,0]]
dfs(3,3)
print(cnt/4)
