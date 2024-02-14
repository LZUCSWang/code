import os
import sys
from math import gcd as g
cnt=0
for i in range(1,2021):
  for j in range(1,2021):
    if g(i,j)==1:
      cnt+=1
print(cnt)
# 请在此输入您的代码