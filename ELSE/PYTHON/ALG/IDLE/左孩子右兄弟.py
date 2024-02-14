#左孩子右兄弟
n=int(input())
data=[[] for _ in range(n+1)]
for i in range(2,n+1):
    t=int(input())
    data[t].append(i)
def dfs(last):
    if len(data[last])==0:
        return 0
    cnt=0
    for i in data[last]:
        cnt=max(cnt,dfs(i)+len(data[last]))
    return cnt
print(data)
print(dfs(1))
