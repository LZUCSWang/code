n=int(input())
flag=[1]*(n+1)
flag[1]=0
s=[0]*(n+1)
def sushu(n):
    k=0
    for i in range(2,n+1):
        for j in range(2,i):
            if i%j==0:
                flag[i]=0
    for i in range(1,n+1):
        if flag[i]==1:
            s[k]=i
            k+=1
    return k
dp=[0]*(n+1)
dp[0]=1
for i in range(sushu(n)):
    for j in range(s[i],n+1):
        dp[j]+=dp[j-s[i]]
print(dp[-1])