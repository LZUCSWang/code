#dp[i][j] 从i到j i是二进制数.
v=[[False]*22 for _ in range(22)]
import math
for i in range(1,22):
    for j in range(i+1,22):
        if math.gcd(i,j)==1:
            v[i][j]=v[j][i]=True
dp=[]
for i in range(0,1<<21):
    for j in range(1,22):
        if i&(1<<j)==0:
            continue
        for k in range(1,22):
            if i&(1<<k) or v[j][k]==False:
                continue
            dp[i+(1<<k)][j]+=dp[i][j]
                    