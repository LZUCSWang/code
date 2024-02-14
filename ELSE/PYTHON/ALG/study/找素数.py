import os
import sys
def judge(x):
  for i in range(2,int(x**0.5)+1):
    if x%i==0:
      return False
  return True
cnt=0
i=2
while cnt<100002:
  if judge(i):
    cnt+=1
  i+=1
print(i)
# 请在此输入您的代码