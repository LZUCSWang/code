import sys
sys.setrecursionlimit(1000000)
n=int(input())
def dfs(son):
    f[son][0]=0
    f[son][1]=1
    for theson in graph[son]:
        dfs(theson)
        f[son][1]+=min(f[theson][0],f[theson][1])
        f[son][0]+=f[theson][1]
f=[[0]*2 for _ in range(n)]
graph=[[] for _ in range(n)]
for i in range(n):
    s=list(map(int,input().split()))
    if s[1]==0:
        continue
    graph[s[0]].extend(s[2:])
dfs(0)
print(min(f[0]))