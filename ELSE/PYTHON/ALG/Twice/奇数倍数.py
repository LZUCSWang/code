import os
import sys
bei=1
def check(x):
  for i in str(x):
    if i in '02468':
      return 0
  return 1
t=2019
while bei>0:
  x=t*bei
  bei+=2
  if check(x):
    print(x)
    sys.exit()
# 请在此输入您的代码