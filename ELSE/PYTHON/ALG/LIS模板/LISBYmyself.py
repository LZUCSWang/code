import sys
def upper_bound(recordlist,target):
    record_len=len(recordlist)
    left,right,pos=0,record_len-1,record_len
    if record_len==0:
        return 0
    if target>recordlist[right]:
        return pos
    else:
        while left<=right:
            mid=(left+right)//2
            if recordlist[mid]<target:
                left=mid+1
            else:
                right=mid-1
            pos=right
        return left
def LIS(data):
    data_len=len(data)
    recordlist=[]
    for i in range(data_len):
        pos=upper_bound(recordlist,data[i])
        if len(recordlist)==0:
            recordlist.append(data[i])
        elif pos==len(recordlist):
            recordlist.append(data[i])
        else:
            recordlist[pos]=data[i]
    print(recordlist)
    return len(recordlist)
