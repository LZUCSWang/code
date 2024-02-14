#最大约数和
s=int(input())
yueshu=[0]*(s+1)
dp=[0]*(s+1)
for i in range(1,s+1):
    for j in range(i*2,s+1,i):
        yueshu[j]+=i
for i in range(2,s+1):
    for j in range(i,s+1):
        dp[j]=max(dp[j],dp[j-i]+yueshu[i])
print(dp[-1])
