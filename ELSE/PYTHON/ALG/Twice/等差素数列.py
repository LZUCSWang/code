import os
import sys
def check(x):
  for i in range(2,x):
    if x%i==0:
      return 0
  return 1
for d in range(2,1000000000000000):
  for a1 in range(2,1000):
    flag=1
    na=a1
    if check(a1):
      flag=0
      for i in range(1,10):
        na=na+d
        if not check(na):
          flag=1
          break
    if flag==0:
      print(d)
      sys.exit()
# 请在此输入您的代码