#精卫填海01背包
v,n,c=map(int,input().split())
weight,value,dp=[0]*n,[0]*n,[0]*(c+1)
for i in range(n):
    value[i],weight[i]=map(int,input().split())
for i in range(n):
    for j in range(c,weight[i]-1,-1):
        dp[j]=max(dp[j],dp[j-weight[i]]+value[i])
if dp[-1]<v:
    print("Impossible")
else:
    for i in range(c,-1,-1):
        if dp[i]<v:
            print(c-i-1)
            break
        
