from itertools import permutations as p
n=int(input())
cnt=[0]*20
t=0
for i in p([i for i in range(1,n+1)]):
    cnt=0
    for j in range(1,len(i)):
        for k in range(j):
            if i[k]<i[j]:
                cnt+=1
    # print(cnt,end=' ')
    t+=1
    cnt[cnt]+=1
# print(cnt)
# print(t)
for i in range(len(cnt)):
    cnt+=cnt[i]*i
print(cnt)
# def slove(i):
#     cnt=0
#     for up in range((i-1)*(i-2)//2+1,(i)*(i-1)//2+1):
#         cnt+=up*6-9
#     return cnt
# n=int(input())
# dp=[0]*(n+1)
# dp[2]=1
# dp[3]=9
# for i in range(4,n+1):
#     dp[i]=dp[i-1]+slove(i)
# print(dp[n]%998244353)