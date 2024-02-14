n=int(input())
data=[0]+list(map(int,input().split()))
graph=[[] for _ in range(n+1)]
for i in range(n-1):
    datas,b=map(int,input().split())
    graph[datas].append(b)
    graph[b].append(datas)
import sys

f=[-float('inf')]*(n+1)
def dfs(son,father):#以root为跟的子树最大值
    f[son]=data[son]
    for j in graph[son]:
        if j!=father:
            dfs(j,son)
            if f[j]>0:
                f[son]+=f[j]
dfs(1,0)
print(max(f))
