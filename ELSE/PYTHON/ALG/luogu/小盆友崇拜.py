import sys
sys.setrecursionlimit(1000000)
n=int(input())
f=[0]+list(map(int,input().split()))
vis=[0]*(n+1)
global cnt
cnt=0
def dfs(u,i):
    if vis[u]:
        global cnt
        cnt=max(cnt,i-vis[u])
        return 
    vis[u]=i
    dfs(f[u],i+1)
for i in range(1,n+1):
    if not vis[i]:dfs(i,1)
print(cnt)