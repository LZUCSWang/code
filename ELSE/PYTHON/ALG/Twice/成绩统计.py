import os
import sys
jige,youxiu=0,0
n=int(input())
for i in range(n):
  datas=int(input())
  if datas>=60:
    jige+=1
  if datas>=85:
    youxiu+=1
print("%.0f"%(jige*100/n)+'%')
print("%.0f"%(youxiu*100/n)+'%')
# 请在此输入您的代码