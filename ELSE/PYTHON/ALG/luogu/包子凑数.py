import os
import sys
from math import gcd

n=int(input())
data=[int (input()) for _ in range(n)]
dp=[0]*100000
g=data[0]
for i in range(n):
  g=gcd(g,data[i])
if g!=1:
  print("INF")
  sys.exit()
dp[0]=1
for i in range(n):
  for j in range(data[i],100000):
    dp[j]=max(dp[j],dp[j-data[i]])
print(dp.count(0))
# 请在此输入您的代码