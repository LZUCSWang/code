def getvalue(dp,x,y,z):
    if x>row or x<=0 or y>col or y<=0 or z>step or z<=0 :
        return 0
    return dp[z][x][y]
row,col,x,y,step=map(int,input().split())
dp=[[[0]*col]*row]*(step+1)
dp[0][x-1][y-1]=1
for high in range(1,step+1):
    for i in range(row):
        for j in range(col):
            dp[high][i][j]=getvalue(dp,x-1,y,high-1)+getvalue(dp,x,y-1,high-1)+getvalue(dp,x+1,y,high-1)+getvalue(dp,x,y+1,high-1)
print(sum(dp[step])/(4**step))