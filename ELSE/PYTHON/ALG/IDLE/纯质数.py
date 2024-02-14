#纯质数
#质数筛
n=20210605
flag=[True]*(n+1)
flag[0]=flag[1]=False
for i in range(2,n+1):
    if flag[i]:
        for k in range(2*i,n+1,i):
            flag[k]=False
cnt=0
for i in range(2,n+1):
    if flag[i]:
        flag1=True
        for j in str(i):
            if flag[int(j)]==False:
                flag1=False
                break
        if flag1:
            cnt+=1
print(cnt)
