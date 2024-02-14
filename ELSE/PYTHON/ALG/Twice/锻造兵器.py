n,c=map(int,input().split())
cnt=0
quyou,quzuo=0,0
data=list(map(int,input().split()))
data.sort()
for i in range(n):
    while quyou<n and  data[quyou]-data[i]<c:
        quyou+=1
    while quzuo<n and data[quzuo]-data[i]<=c:
        quzuo+=1
    if quyou<n and data[quyou]-data[i]==c:
        cnt+=quzuo-quyou
print(cnt)