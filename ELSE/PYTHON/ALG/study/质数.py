import os
import sys
def judge(nums)->bool:
  for i in range(2,nums):
    if nums%i==0:
      return False
  return True
cnt=[]
flag=0
i=2
while i>0:
  if judge(i):
    cnt.append(i)
  if len(cnt)==2019:
    print(cnt[-1])
    break
  i+=1
# 请在此输入您的代码