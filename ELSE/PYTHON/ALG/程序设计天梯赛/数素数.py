#素数筛

m,n=map(int,input().split())
flag=[True]*(1000000)
temp=0
cnt=0
for i in range(2,1000000):
    if flag[i]:
        cnt+=1
        if cnt>n:
            break
        if cnt>=m and cnt<=n:
            print(i,end='')
            temp+=1
            if temp==10:
                temp=0
                print()
            elif cnt!=n:
                print(end=' ')
        for k in range(2*i,1000000,i):
            flag[k]=False