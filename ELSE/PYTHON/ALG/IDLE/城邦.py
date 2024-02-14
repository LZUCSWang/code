#最小生成树
def cost(x,y):#计算权值
    s=0
    while x or y:
        if x%10 !=y%10:
            s+=x%10+y%10
        x//=10
        y//=10
    return s
print(cost(2021,922))
last=[i for i in range(2022)]

import sys
#sys.exit()
def find(x):
    if last[x]!=x:
        last[x]=find(last[x])
    return last[x]
def union(x,y):
    root_x,root_y=find(x),find(y)
    if root_x!=root_y:
        last[root_x]=last[root_y]
edge=[(i,j,cost(i,j)) for i in range(1,2022) for j in range(1,2022)]
edge.sort(key=lambda x:x[2])
cnt=0
cnt=0
for item in edge:
    x,y,c=item[0],item[1],item[2]
    try:
        if find(x)!=find(y) and cnt<2020:
            union(x,y)
            cnt+=c
            cnt+=1
    except:
        print(x,y)
        sys.exit()
print(cnt)
        
