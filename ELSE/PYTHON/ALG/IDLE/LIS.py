#LIS
#最大上升子序列
def upper_bound(arry,target):
    arry_len=len(arry)
    left,right=0,arry_len-1
    if arry_len==0:
        return 0
    if target>arry[right]:
        return arry_len
    while left<=right:
        mid=(left+right)//2
        if arry[mid]>=target:
            right=mid-1
        else:
            left=mid+1
    return left
def LIS(arry):
    arry_len=len(arry)
    cntarry=[]
    for i in range(arry_len):
        pos=upper_bound(cntarry,arry[i])
        if len(cntarry)==0 or pos==len(cntarry):
            cntarry.append(arry[i])
        else:
            cntarry[pos]=arry[i]
    return len(cntarry)

def erfen(arry,target):
    arry_len=len(arry)
    left,right=0,arry_len-1
    if arry_len==0:
        return 0
    if target<=arry[right]:
        return arry_len
    while left<=right:
        mid=(left+right)//2
        if arry[mid]<target:
            right=mid-1
        else:
            left=mid+1
    return left
def bushangshen(arry):
    arry_len=len(arry)
    cntarry=[]
    for i in range(arry_len):
        pos=erfen(cntarry,arry[i])
        if len(cntarry)==0 or pos==len(cntarry):
            cntarry.append(arry[i])
        else:
            cntarry[pos]=arry[i]
    return len(cntarry)
data=list(map(int,input().split()))
print(bushangshen(data))
print(LIS(data))
