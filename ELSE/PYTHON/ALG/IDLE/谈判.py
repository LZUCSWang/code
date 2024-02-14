#谈判
n=int(input())
data=list(map(int,input().split()))
data.sort()
cnt=0
last=data[0]
for i in range(1,n):
    temp=last+data[i]
    last=temp
    cnt+=temp
print(cnt)
