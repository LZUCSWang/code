m=int(input())
data=list(map(int,input().split()))
dp=[[0]*(sum(data)+1) for _ in range(m+1)]
dp[0][0]=1
data.sort(reverse=True)
data=[0]+data
for i in range(1,m+1):
    for j in range(sum(data)+1):
        if dp[i-1][j]==1:
            dp[i][j]=1
            dp[i][j+data[i]]=1
            if j-data[i]>0:
                dp[i][j-data[i]]=1
print(sum(dp[-1])-1)