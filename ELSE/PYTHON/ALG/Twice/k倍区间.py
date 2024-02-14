import sys
import os
n, k = map(int, input().split())
dp = [0]*(n+1)
cnt = 0
data=[0]*(n+1)
count=[0]*k
for i in range(1, n+1):
    data[i]=int(input())
    dp[i] = (dp[i-1]+data[i])%k
    count[dp[i]]+=1
for i in range(1,k):
    cnt+=(count[i]-1)*count[i]//2
print(cnt+dp.count(0))
