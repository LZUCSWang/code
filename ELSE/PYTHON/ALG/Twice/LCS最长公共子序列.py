n, m = map(int, input().split())
nm=max(n,m)
datas = [0]+list(map(int, input().split()))
b = [0]+list(map(int, input().split()))
dp=[[0]*(nm+1) for i in range(nm+1)]
for i in range(1,n+1):
    for j in range(1,m+1):
        if datas[i]==b[j]:
            dp[i][j]=dp[i-1][j-1]+1
        else:
            dp[i][j]=max(dp[i-1][j],dp[i][j-1])
mv=0
for i in range(len(dp)):
    mv=max(mv,max(dp[i]))
print(mv)