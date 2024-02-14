n,p=map(int,input().split())
anss,lasts,dpp=[0,0],[0,0],[0,0]
nums=[0]+list(map(int,input().split()))
ans=anss[1]=lasts[1]=dpp[1]=nums[1]
for i in range(2,n+1):
    lasts[i&1]=(max(nums[i],lasts[(i-1)&1]+nums[i]))
    dpp[i&1]=(max(lasts[i&1],dpp[(i-1)&1]))
    anss[i&1]=(nums[1]*2 if i==2 else max(anss[(i-1)&1],dpp[(i-1)&1]+anss[(i-1)&1]))
    ans=max(ans,anss[i&1])
if (ans<0):
    print('-',end='')
print(abs(ans)%p)