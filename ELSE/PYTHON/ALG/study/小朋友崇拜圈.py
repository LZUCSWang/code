def dfs(x):
    global cnt,maxcnt,i
    if visited[data[x]-1]==0:
        visited[data[x]-1]=1
        cnt+=1
        dfs(data[x]-1)
        visited[data[x]-1]=0 
    elif x==i:
        maxcnt=max(cnt,maxcnt)
        return 
n=int(input())
data=list(map(int,input().split()))
visited=[0]*n
maxcnt=0
for i in range(n):
    cnt=0
    dfs(i)
print(maxcnt)

