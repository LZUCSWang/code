import os
import sys
n,x=map(int,input().split())
data=list(map(int,input().split()))
seen=[0]*n
def dfs(step,s):
    if s>x :
        return 
    if s==x:
        print("Y")
        sys.exit()
    for i in range(step,n):
        if seen[i]==0:
            seen[i]=1
            dfs(step+1,s+data[i])
            seen[i]=0
dfs(0,0)
print("N")