"""n=int(input())
data=[[0]*(n+1) for _ in range(n+1)]
while 1>0:
    x,y,value=map(int,input().split())
    if x==0 and y==0 and value==0:
        break
    data[x][y]=value
f=[[[[0 for _ in range(n+1)] for _ in range(n+1)] for _ in range(n+1)] for _ in range(n+1)]
for i in range(1,n+1):
    for j in range(1,n+1):
        for k in range(1,n+1):
            for l in range(1,n+1):
                f[i][j][k][l]=max(f[i-1][j][k-1][l],f[i-1][j][k][l-1],f[i][j-1][k-1][l],f[i][j-1][k][l-1])+data[i][j]+data[k][l]
                if i==k and j==l:
                    f[i][j][k][l]=f[i][j][k][l]-data[i][j]
print(f[n][n][n][n])"""
n=int(input())
data=[[0]*(n+1) for _ in range(n+1)]
while 1>0:
    x,y,v=map(int,input().split())
    if x==0 and y==0 and v==0:
        break
    data[x][y]=v
f=[[[[0 for _ in range(n+1)] for _ in range(n+1)] for _ in range(n+1)] for _ in range(n+1)]
for i in range(1,n+1):
    for j in range(1,n+1):
        for k in range(1,n+1):
            for l in range(1,n+1):
                f[i][j][k][l]=max(f[i-1][j][k-1][l],f[i-1][j][k][l-1],f[i][j-1][k][l-1],f[i][j-1][k-1][l])+data[i][j]+data[k][l]
                if i==k and j==l:
                    f[i][j][k][l]-=data[i][j]
print(f[n][n][n][n])