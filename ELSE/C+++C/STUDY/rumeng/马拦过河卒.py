n,m,x,y=map(int,input().split())
dp=[[1]*(m+1) for _ in range(n+1)]
dp[x][y]=0
def mazou(xx,yy):
    if xx>=0 and xx<=n and yy>=0 and yy<=m:
        dp[xx][yy]=0
mazou(x+1,y+2)
mazou(x+2,y+1)
mazou(x-1,y+2)
mazou(x-2,y+1)
mazou(x-1,y-2)
mazou(x-2,y-1)
mazou(x+1,y-2)
mazou(x+2,y-1)
if dp[0][0]==0:
    print(0)
    exit()
for i in range(m+1):
    if dp[0][i]==1:
        continue
    for j in range(i+1,m+1):
        dp[0][j]=0
    break
for i in range(n+1):
    if dp[i][0]==1:
        continue
    for j in range(i+1,n+1):
        dp[j][0]=0
    break
for i in range(1,n+1):
    for j in range(1,m+1):
        if dp[i][j]==0:
            continue
        dp[i][j]=dp[i-1][j]+dp[i][j-1]
print(dp[n][m])
