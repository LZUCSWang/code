#素数筛
N=1000
flag=[True]*(N+1)
flag[1]=False
for i in range(1,N+1):
    if flag[i]:
        print(i)
        for k in range(i*2,N+1,i):
            flag[k]=False
