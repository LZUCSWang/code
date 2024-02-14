n=int(input())
cnt=0
hang=[0]*100
arr=[]
def checkzuoxia(i,j):
    for point in arr:
        if point[0]+point[1]==i+j and i-3<point[0]:
            return 1
    return 0
def checkyouxia(i,j):
    for point in arr:
        if i-point[0]==j-point[1] and i-3<point[0]:
            return 1
    return 0
def deal(i,j,x):
    if x==1:
        hang[j]=1
        arr.append((i,j))
    else:
        hang[j]=0
        arr.pop()
def check(i,j):
    if hang[j]==1 or checkyouxia(i,j) or checkzuoxia(i,j):
        return 0
    return 1
def dfs(i):
    global n,cnt
    if i>=n:
        cnt+=1
        return
    for j in range(n):
        if check(i,j)==1:
            deal(i,j,1)
            dfs(i+1)
            deal(i,j,0)
dfs(0)
print(cnt)
# 请在此输入您的代码
