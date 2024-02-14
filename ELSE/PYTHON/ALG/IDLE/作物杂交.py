#作物杂交
n,m,k,t=map(int,input().split())
time=[0]+list(map(int,input().split()))
have=list(map(int,input().split()))
methods=[[] for _ in range(n+1)]
min_time=[float('inf') ]*(n+1)
for i in range(k):
    datas,b,c=map(int,input().split())
    temp=[datas,b,max(time[datas],time[b])]
    methods[c].append(temp)
for i in have:
    min_time[i]=0
def dfs(target):
    if min_time[target]!=float('inf'):
        return min_time[target]
    for mtd in methods[target]:
        min_time[target]=min(min_time[target],max(dfs(mtd[0]),dfs(mtd[1]))+mtd[2])
    return min_time[target]
print(dfs(t))

