#膜拜
n,m=map(int,input().split())
data=[int(input()) for _ in range(n)]
data=[0]+data
dp=[float('inf')]*(n+1)
dp[0]=0
dp[1]=1
s1,s2=[0]*(n+1),[0]*(n+1)
for i in range(1,n+1):
    if data[i]==1:
        s1[i]=s1[i-1]+1
        s2[i]=s2[i-1]
    else:
        s2[i]=s2[i-1]+1
        s1[i]=s1[i-1]
def sm(k,i,j):
    if k==1:
        return s1[j]-s1[i-1]
    return s2[j]-s2[i-1]
for i in range(1,n+1):
    for j in range(1,i+1):
        if sm(1,i,j)==0 or sm(2,i,j)==0 or abs(sm(1,i,j)-sm(2,i,j))<=m:
            dp[i]=min(dp[i],dp[j-1]+1)
print(dp[-1])
