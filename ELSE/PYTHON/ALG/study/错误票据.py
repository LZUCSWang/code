n=int(input())
data=[]
for i in range(n):
    temp=list(map(int,input().split()))
    for j in range(len(temp)):
        data.append(temp[j])
data.sort()
ab,chon=-1,-1
for i in range(data[0],data[-1]+1):
    if ab!=-1 and chon!=-1:
        break
    if i not in data:
        ab=i
    if data.count(i)==2:
        chon=i
print("%d %d"%(ab,chon))
