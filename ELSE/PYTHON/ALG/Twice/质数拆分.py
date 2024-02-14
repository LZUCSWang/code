n=7
#埃筛
cnt=[]
flag=[True for i in range(2020)]
for i in range(2,n+1):
    if flag[i]:
        cnt.append(i)
        for k in range(2*i,n+1,i):
            flag[k]=False
print(cnt)
dp=[0]*(n+1)
# dp[2]=1
#01背包
for i in cnt:
    for j in range(n,i-1,-1):
        if i==j:
            dp[j]+=1
        dp[j]+=dp[j-i]
print(dp)