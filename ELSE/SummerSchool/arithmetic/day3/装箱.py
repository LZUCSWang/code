n=int(input())
data=list(map(int,input().split()))
box=[100]*n
mj=0
for i in range(n):
    for j in range(n):
        if data[i]<=box[j]:
            box[j]-=data[i]
            print(data[i],j+1)
            mj=max(j,mj)
            break
print(mj+1)