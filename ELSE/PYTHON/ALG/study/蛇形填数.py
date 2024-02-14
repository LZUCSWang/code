import os
import sys
i,j=0,0
flag=-1
current=1
while i!=19 or j!=19:
    if i==0 and flag==-1:
        j+=1
        flag=flag*-1
        current+=1
    elif j==0 and flag==1:
        i+=1
        flag=flag*-1
        current+=1
    if flag==1:
        i+=1
        j-=1
    else:
        i-=1
        j+=1
    current+=1
print(current)
  
# 请在此输入您的代码