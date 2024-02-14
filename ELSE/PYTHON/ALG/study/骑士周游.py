def pro(x,y,step):
    if x>8 or x<0 or y>9 or y<0:
        return 0
    if step==0:
        if x==0 and y==0 :
            return 1
        else:
            return 0
    return pro(x+2,y+1,step-1)+pro(x+1,y+2,step-1)+pro(x-1,y+2,step-1)+pro(x-2,y+1,step-1)+pro(x-1,y-2,step-1)+pro(x-2,y-1,step-1)+pro(x+1,y-2,step-1)+pro(x+2,y-1,step-1)

step=6
def getvalue(dp,x,y,z):
    if x>8 or x<0 or y>9 or y<0 or z>step or z<0:
        return 0
    return dp[x][y][z]
dp=[[[0]*9]*10]*step
dp[0][0][0]=1
for h in range(1,step):
    for i in range(9):
        for j in range(10):
            dp[i][j][h]+=getvalue(dp,i+1,j+2,h-1)+getvalue(dp,i+2,j+1,h-1)+getvalue(dp,i-1,j+2,h-1)+getvalue(dp,i-2,j+1,h-1)+getvalue(dp,i-1,j-2,h-1)#省略