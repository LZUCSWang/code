#从1到m，m个数中抽n个数从小到大排列
m,n=map(int,input().split())
cnt=[0]*(m+1)
def dfs(i,j):
    global m,n
    if i>n:
        for i in range(1,n+1):
            print(cnt[i],end='')
        print()
        return 
    for k in range(j,m+1):
        cnt[i]=k
        dfs(i+1,k+1)
        cnt[i]=0
dfs(1,1)