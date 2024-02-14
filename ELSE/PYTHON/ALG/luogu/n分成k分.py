def dfs(sum,last,step):
    if sum>n:
        return 
    if step==k:
        global cnt
        if sum==n:
            cnt+=1
        return 
    for i in range(last,n+1):
        dfs(sum+i,i,step+1)
cnt=0
n,k=map(int,input().split())
dfs(0,1,0)
print(cnt)
