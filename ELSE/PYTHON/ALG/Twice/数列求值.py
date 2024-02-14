import os
import sys
datas,b,c,d=1,1,1,0
for i in range(4,20190324):
  d=(datas+b+c)%10000
  datas,b,c,d=b,c,d,0
print((datas+b+c)%10000)