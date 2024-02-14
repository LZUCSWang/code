import os
import sys
n=int(input())
sumdata=[0]*(n)
data=list(map(int,input().split()))
sumdata[0]=data[0]
for i in range(1,n):
  sumdata[i]=sumdata[i-1]+data[i]

dp=[[0]*(n+1) for _ in range(n+1)]
for i in range(n):
    dp[i][i]=0
for jiange in range(1,n):
    for left in range(0,n-jiange):
        right=left+jiange
        dp[left][right]=float('inf')
        if left==0:
            sumtemp=sumdata[right]
        else:
            sumtemp=sumdata[right]-sumdata[left-1]
        for zhong in range(left,right):
            dp[left][right]=min(dp[left][right],dp[left][zhong]+dp[zhong+1][right]+sumtemp)
print(dp[0][n-1])
# 请在此输入您的代码