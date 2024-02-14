import os
import sys
n,m=map(int,input().split())
data=list(map(int,input().split()))
data.sort(reverse=True)
print(sum(data[:n+1])-sum(data[n+1:]))
# 请在此输入您的代码