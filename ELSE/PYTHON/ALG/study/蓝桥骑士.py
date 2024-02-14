import os
import sys
n=int(input())
data=list(map(int,input().split()))
m,c=data[0],1
for i in range(1,n):
  if data[i]>m:
    c+=1
    m=data[i]
print(c)

# 请在此输入您的代码