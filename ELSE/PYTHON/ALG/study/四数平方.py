import math
import sys
x=int(input())
t=[0]*3
def dfs(nowplace,x,last):
    end=int(x**0.5)
    if nowplace>2:
        if end>=last and end*end==x:
            print(t[0],t[1],t[2],end)
            sys.exit()
        return 
    for i in range(last,end+1):
        t[nowplace]=i
        dfs(nowplace+1,x-i*i,i)
dfs(0,x,0)