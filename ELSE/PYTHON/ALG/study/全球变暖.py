n=int(input())
cnt=0
graph=[]
for i in range(n):
    graph.append(input())
q=[]
flag=True
visited=[[0]*n for _ in range(n)]
flags=[(0,1),(0,-1),(1,0),(-1,0)]
def bfs(x,y):
    global flag
    visited[x][y]=1
    q.append((x,y))
    while len(q)>0:
        item=q.pop(0)
        x1,y1=item[0],item[1]
        if graph[x1-1][y1]=='#' and graph[x1][y1-1]=='#' and graph[x1+1][y1]=='#' and graph[x1][y1+1]=='#':
            flag=False
        for i in flags:
            nx=x1+i[0]
            ny=y1+i[1]
            if graph[nx][ny]=='#' and visited[nx][ny]==0:
                visited[nx][ny]=1
                q.append((nx,ny))
for i in range(n):
    for j in range(n):
        if graph[i][j]=='#' and visited[i][j]==0:
            flag=True
            bfs(i,j)
            if flag==False:
                cnt+=1
print(cnt)