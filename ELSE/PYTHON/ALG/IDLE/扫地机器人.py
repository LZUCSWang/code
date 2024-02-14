#扫地机器人
def check(lenth):
    R=0
    for i in range(1,k+1):
        if R+lenth<datas[i]:
            return False
        if R>datas[i]:
            R=datas[i]+lenth-1
        else:
            R+=lenth
    return R>=n
n,k=map(int,input().split())
datas=[0]*(k+1)
for i in range(1,k+1):
    datas[i]=int(input())
datas.sort()
left,right=0,100000
while left<right:
    mid=(left+right)//2
    if check(mid):
        right=mid-1
    else:
        left=mid+1
print(left*2)
