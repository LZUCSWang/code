n,m=map(int,input().split())
data=[]
for i in range(n):
    data.append(list(map(int,input().split())))
# print(data)
dir=[[0,m-1] for i in range(n)]
ans=0
pow2=1
for i in range(1,m+1):
    pow2*=2
    for j in range(n):
        if dir[j][0]>dir[j][1]:
            continue
        if data[j][dir[j][0]]>data[j][dir[j][1]]:
            ans+=pow2*data[j][dir[j][1]]
            dir[j][1]-=1
        else:
            ans+=pow2*data[j][dir[j][0]]
            dir[j][0]+=1
print(ans)
