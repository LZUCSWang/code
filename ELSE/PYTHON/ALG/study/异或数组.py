T=int(input())
nums=[0 for i in range(23)]
def dealnums(x):
    for i in range(20,-1,-1):
        if (x>>i)&1==1:
            nums[i+1]+=1
            
while T>0:
    T-=1
    data=[]
    sum=0
    inputt=list(map(int,input().split()))
    lenth=inputt[0]
    for i in range(1,lenth+1):
        data.append(inputt[i])
    for i in range(lenth):
        dealnums(data[i])
        sum^=data[i]
    if sum==0:
        print('0')
        continue
    print(nums)
    for i in range(20,0,-1):
        if nums[i]==1:
            print('1')
            break
        if nums[i]%2==1 and lenth%2==1:
            print('1')
            break
        if nums[i]%2==1 and lenth%2==0:
            print('0')
            break
    