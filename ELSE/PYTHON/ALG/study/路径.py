def lcm(x,y):
    z=max(x,y)
    while z>0:
        if z%x==0 and z%y==0:
            return z
        z+=1
print(lcm(6,8))
n=2021
dp=[float('inf')]*(n+1)
dp[1]=0
for i in range(1,2022):
    for j in range(i+1,i+22):
        dp[j]=min(dp[j],dp[i]+lcm(i,j))
print(dp[2021])