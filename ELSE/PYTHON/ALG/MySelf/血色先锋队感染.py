import sys
n,m,datas,b=map(int,input().split())
data=[[0]*(m+1) for _ in range(n+1)]
queue,cnt,flags=[],[],[(0,1),(1,0),(0,-1),(-1,0)]
for i in range(datas):
    x,y=map(int,sys.stdin.readline().split())
    data[x][y]=1
    queue.append((x,y,0))
end=[0]*(b)
for i in range(b):
    x,y=map(int,sys.stdin.readline().split())
    cnt.append((x,y))
while len(queue)>0:
    item=queue.pop(0)
    x,y,t=item[0],item[1],item[2]
    for d in flags:
        nx,ny=x+d[0],y+d[1]
        if nx>0 and ny>0 and nx<=n and ny<=m and data[nx][ny]==0:
            data[nx][ny]=1

            if (nx,ny) in cnt:
                end[cnt.index((nx,ny))]=t+1
            queue.append((nx,ny,t+1))
for i in range(b):
    print(end[i])