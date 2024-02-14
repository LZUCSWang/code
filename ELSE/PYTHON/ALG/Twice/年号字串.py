import os
import sys
t="0ABCDEFGHIJKLMNOPQRSTUVWXYZ"
cnt=[]
n=2019
while n>0:
  i=n%26
  if i==0:
    cnt.append('Z')
  else:
    cnt.append(t[i])
  n//=26

print(''.join(cnt[::-1]))
# 请在此输入您的代码