import os
import sys
n,m=map(int,input().split())
data=list(map(int,input().split()))
flag=1
for i in range(n-m+1):
  if flag:
    most=min(data[i:i+m])
  else:
    most=min(most,data[i+m-1])
  if most==data[i]:
    flag=1
  else:
    flag=0
  print(most)
# 请在此输入您的代码