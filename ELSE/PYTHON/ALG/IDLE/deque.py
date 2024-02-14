#deque
import os
import sys

from collections import deque
flags=[(0,1),(1,0),(0,-1),(-1,0)]
#全球变暖
def bfs(i,j):
    flag=True
    queue=deque([(i,j)])
    while len(queue)>0:
        item=queue.popleft()
        x,y=item[0],item[1]
        
        if flag and data[x+1][y]=='#' and data[x-1][y]=='#' and data[x][y+1]=='#' and data[x][y-1]=='#' :
            global flag1
            flag1=True
            flag=False
        for d in flags:
            nx,ny=x+d[0],y+d[1]
            if nx>=0 and nx<n and ny>=0 and ny<n and not seen[nx][ny] and data[nx][ny]=='#':
                seen[nx][ny]=True
                queue.append((nx,ny))
n=int(input())
data=[list(input()) for _ in range(n)]
seen=[[False]*n for _ in range(n)]
cnt=0
for i in range(n):
    for j in range(n):
        if not seen[i][j] and data[i][j]=='#':
            flag1=False
            seen[i][j]=True
            bfs(i,j)
            if flag1:cnt+=1
print(cnt)
            
