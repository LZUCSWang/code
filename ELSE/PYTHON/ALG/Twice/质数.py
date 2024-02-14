import os
import sys
time=0
i=3
while time<2019:
  while True:
    flag=0
    for j in range(2,i):
      if i%i==0:
        flag=1
        break
    if flag==0:
      break
    i+=1
  time+=1
print(i)
# 请在此输入您的代码