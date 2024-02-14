import os
import sys
n=int(input())
grades=[]
for i in range(n):
  grades.append(int(input()))
print(max(grades))
print(min(grades))
print("%.0f"%(sum(grades)/n))
# 请在此输入您的代码