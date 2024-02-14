#单调递增子序列
n=int(input())
data=[0]+list(map(int,input().split()))
#左到右单增
dpl=[1]*(n+1)
for i in range(1,n+1):
    for j in range(1,i):
        if data[i]>data[j]:
            dpl[i]=max(dpl[i],dpl[j]+1)
#右到左单增
dpr=[1]*(n+1)
for i in range(n,0,-1):
    for j in range(n,i,-1):
        if data[i]>data[j]:
            dpr[i]=max(dpr[i],dpr[j]+1)
cnt=0
for i in range(1,n+1):
    cnt=max(dpl[i]+dpr[i]-1,cnt)
print(n-cnt)