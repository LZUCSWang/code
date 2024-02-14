#输入n，输出从1到n的全部数字的全排列
n=int(input())
seen,cnt=[0]*(n+1),[0]*(n+1)
def bfs(x):
    if x>n:
        for i in range(1,n+1):
            print(cnt[i],end='')
        print()
        return 
    for y in range(1,n+1):
        if seen[y]==0:
            seen[y]=1
            cnt[x]=y
            bfs(x+1)
            seen[y]=0
print(bfs(1))
"""
123
132
213
231
312
321
"""