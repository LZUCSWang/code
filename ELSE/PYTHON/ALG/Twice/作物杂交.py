n,m,k,t=map(int,input().split())
time=[0]+list(map(int,input().split()))
have=list(map(int,input().split()))
method=[list(map(int,input().split())) for _ in range(k)]
def bfs(x):
    if x in have:
        return 0
    temptime=float('inf')
    for i in range(k):
        if x==method[i][2]:
            datas,b=method[i][0],method[i][1]
            temptime=min(max(bfs(datas),bfs(b))+max(time[datas],time[b]),temptime)
    return temptime
print(bfs(t))