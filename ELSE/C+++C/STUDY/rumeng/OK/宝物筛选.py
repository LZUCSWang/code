n,m=map(int,input().split())
w,v,s=[0]*n,[0]*n,[0]*n
dp=[0]*(m+1)
for i in range(n):
    v[i],w[i],s[i]=map(int,input().split())
for i in range(n):
    for j in range(m,-1,-1):
        for k in range(s[i]+1):
            if j>=w[i]*k:
                dp[j]=max(dp[j],dp[j-w[i]*k]+v[i]*k)
print(dp[-1])