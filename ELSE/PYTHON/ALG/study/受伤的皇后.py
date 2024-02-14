import os
import sys
cnt=0
n=int(input())
for i in range(n):
  for j in range(n):
    for p in range(n):
      for q in range(n):
        if abs(i-p)==abs(j-q) and i-p>=3:
            cnt+=1
        elif i!=p and j!=q:
            cnt+=1
print(cnt)

# 请在此输入您的代码