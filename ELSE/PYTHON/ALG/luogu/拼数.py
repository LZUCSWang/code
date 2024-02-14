n=int(input())
data=list(input().split())
visited=[0]*n
datas=['' for _ in range(n)]
cnt=''
def dfs(step):
    global cnt
    if step>=n:
        temp=''.join(datas)
        if cnt<temp:
            cnt=temp
        return 
    for i in range(n):
        if(visited[i]==0):
            visited[i]=1
            datas[step]=data[i]
            dfs(step+1)
            datas[i]=''
            visited[i]=0
dfs(0)
print(cnt)
