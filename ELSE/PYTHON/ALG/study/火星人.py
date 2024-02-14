import copy
import sys
n=int(input())
addnum=int(input())
start=int(''.join(input().split()))
tempcnt=[]
allcnt=[]
seen=[0]*(n+1)
def dfs(i):
    global addnum
    if i>n:
        cnttemp=int(''.join(map(str,copy.deepcopy(tempcnt))))
        allcnt.append(cnttemp)
        if cnttemp>start:
            addnum-=1
        if addnum==0:
            print(' '.join(str(cnttemp)))
            sys.exit()
        return 
    for j in range(1,n+1):
        if seen[j]==0:
            seen[j]=1
            tempcnt.append(j)
            dfs(i+1)
            tempcnt.pop()
            seen[j]=0
dfs(1)
