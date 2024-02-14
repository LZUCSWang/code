#方格分割
seen=[[0]*7 for _ in range(7)]
seen[3][3]=1
cnt=0
flags=[(0,1),(1,0),(0,-1),(-1,0)]
def dfs(i,j):
    if i==0 or i==6 or j==0 or j==6:
        global cnt
        cnt+=1
        return 
    for d in flags:
        nx,ny=i+d[0],j+d[1]
        if nx>=0 and nx<=6 and ny>=0 and ny<=6 and seen[nx][ny]==0 and seen[6-nx][6-ny]==0:
            seen[nx][ny],seen[6-nx][6-ny]=1,1
            dfs(nx,ny)
            seen[nx][ny],seen[6-nx][6-ny]=0,0
dfs(3,3)
print(cnt//4)
