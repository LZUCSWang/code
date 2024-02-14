"""5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9"""
import sys
import copy
row,col=map(int,sys.stdin.readline().split())
dp=[[0]*col for _ in range(row)]
seen=copy.deepcopy(dp)
data=[list(map(int,sys.stdin.readline().split())) for _ in range(row)]
most,mostplace=0,None
for i in range(row):
    mt=max(data[i])
    if mt>most:
        most=mt
        mostplace=i,data[i].index(mt)
queue=[]
flags=[(0,1),(1,0),(0,-1),(-1,0)]
queue.append(mostplace)
print(dp)
dp[mostplace[0]][mostplace[1]]=1
while len(queue)>0:
    item=queue.pop(0)
    x,y=item[0],item[1]
    for d in flags:
        nx,ny=d[0]+x,d[1]+y
        if nx>=0 and nx<row and ny>=0 and ny<col and dp[nx][ny]==0 and data[x][y]>data[nx][ny]:
            dp[nx][ny]=dp[x][y]+1
            queue.append((nx,ny))
print(dp)


