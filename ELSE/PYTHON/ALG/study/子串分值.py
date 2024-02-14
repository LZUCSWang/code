import os
import sys

# 请在此输入您的代码
s=input()
datas=[-1 for i in range(26)]
count=0
for i in range(len(s)):
  index=ord(s[i])-ord('datas')
  count+=(len(s)-i)*(i-datas[index])
  datas[index]=i
print(count)