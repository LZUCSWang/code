#砝码称重
n=int(input())
data=list(map(int,input().split()))
data.sort(reverse=True)
data=[0]+data
s=sum(data)
dp=[[0]*(s+1) for _ in range(n+1)]
dp[0][0]=1
for i in range(1,n+1):
    for j in range(0,s+1):
        if dp[i-1][j]==1:
            if dp[i][j]==0:
                dp[i][j]=1
            if dp[i][j+data[i]]==0:
                dp[i][j+data[i]]=1
            if j>=data[i] and dp[i][j-data[i]]==0:
                dp[i][j-data[i]]=1
print(sum(dp[-1])-1)
