n,k=map(int,input().split())
data=[tuple(map(int,input().split())) for _ in range(n)]
data.sort(key=lambda x:x[0])
data=[0]+data
dp=[[float('inf')]*(n-k+1) for _ in range(n+1)]
for nowindex in range(1,n+1):
    dp[nowindex][1]=0
    for lenth in range(1,min(nowindex,n-k)+1):
        for qianmian in range(1,nowindex):
            dp[nowindex][lenth]=min(dp[nowindex][lenth],dp[qianmian][lenth-1]+abs(data[nowindex][1]-data[qianmian][1]))
cnt=float('inf')
for i in range(1,n+1):
    cnt=min(dp[i][-1],cnt)
print(cnt)
