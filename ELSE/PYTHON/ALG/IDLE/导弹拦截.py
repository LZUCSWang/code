#导弹拦截
#最长上升子序列
def shangpu(arry,target):
    arry_len=len(arry)
    left,right=0,arry_len-1
    if arry_len==0:
        return 0
    if target>arry[-1]:
        return arry_len
    while left<=right:
        mid=(left+right)//2
        if arry[mid]<target:
            left=mid+1
        else:
            right=mid-1
    return left
def UP(arry):
    arry_len=len(arry)
    cnt_arry=[]
    for i in range(arry_len):
        pos=shangpu(cnt_arry,arry[i])
        if len(cnt_arry)==0:
            cnt_arry.append(arry[i])
        elif pos==len(cnt_arry):
            cnt_arry.append(arry[i])
        else:
            cnt_arry[pos]=arry[i]
    #print(cnt_arry)
    return len(cnt_arry)
def xiapu(arry,target):
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
def notUP(arry):
    arry_len=len(arry)
    cnt_arry=[]
    for i in range(arry_len):
        pos=xiapu(cnt_arry,arry[i])
        if len(cnt_arry)==0 or pos==len(cnt_arry):
            cnt_arry.append(arry[i])
        else:
            cnt_arry[pos]=arry[i]
    #print(cnt_arry)
    return len(cnt_arry)
data=list(map(int,input().split()))
print(notUP(data))
print(UP(data))
# 6 4 2 1      4
#0,3  mid 1

