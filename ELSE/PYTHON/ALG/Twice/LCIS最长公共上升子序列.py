n,m=map(int,input().split())
nm=max(n,m)
dp=[[0]*(nm+1) for _ in range(nm+1)]
datas=[0]+list(map(int,input().split()))
b=[0]+list(map(int,input().split()))
for i in range(1,n+1):
    maxv=0
    for j in range(1,m+1):
        if datas[i]==b[j]:
            dp[i][j]=maxv+1
        else:
            dp[i][j]=dp[i-1][j]
        if b[j]<datas[i]:
            maxv=max(maxv,dp[i-1][j])
mv=0
for i in range(len(dp)):
    mv=max(mv,max(dp[i]))
print(mv)