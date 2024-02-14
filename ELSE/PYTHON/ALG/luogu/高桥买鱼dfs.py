n,m=map(int,input().split())
data=[]
for i in range(n):
    data.append(input())
    if 's' in data[-1]:
        start=i,data[-1].index('s')
    if 'g' in data[-1]:
        end=i,data[-1].index('g')
# print(start,end)
import sys
seen=[[0]*m for _ in range(n)]
flags=[(0,1),(1,0),(0,-1),(-1,0)]
def dfs(i,j):
    if i==end[0] and j==end[1]:
        print("Yes")
        sys.exit()
    for d in flags:
        nx,ny=i+d[0],j+d[1]
        if nx>=0 and ny>=0 and nx<n and ny<m and (data[nx][ny]=='.' or data[nx][ny]=='g') and seen[nx][ny]==0:
            seen[nx][ny]=1
            dfs(nx,ny)
            seen[nx][ny]=0
dfs(start[0],start[1])
print("No")