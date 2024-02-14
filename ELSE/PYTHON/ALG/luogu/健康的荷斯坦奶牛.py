# def check(temp):
#     for i in range(v):
#         if temp[i]<target[i]:
#             return False
#     return True
# import copy
# def dfs(cnt,i,temp):
#     if check(temp):
#         return
#     for j in range(i,n+1):
#         save=copy.deepcopy(temp)
#         if seen[j]==0 :
#             seen[j]=1
#             for k in range(v):
#                 save[v]+=data[j][v]
#             dfs(cnt+1,j,save)
#             seen[j]=0
import sys
from itertools import combinations as c
v = int(input())
target = list(map(int, input().split()))
g = int(input())
data = [list(map(int, input().split())) for _ in range(g)]
iter = [i for i in range(1, g+1)]
for i in range(1, g+1):
    for item in c(iter, i):
        temp = [0]*v
        flag = True
        for j in range(i):
            for k in range(v):
                temp[k] += data[item[j]-1][k]
                if j == i-1:
                    if temp[k] < target[k]:
                        flag = False
                        break
        if flag:
            print(i,*item)
            sys.exit()
