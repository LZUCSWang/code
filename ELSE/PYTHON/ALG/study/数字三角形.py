import os
import sys
lines = int(input())
inputinfor = []
for i in range(lines):
    temp = input().split()
    temp1 = []
    for j in range(i+1):
        temp1.append(int(temp[j]))
    inputinfor.append(temp1)
for i in range(1,lines):
    for j in range(i+1):
        if j==0:
            inputinfor[i][0]+=inputinfor[i-1][0]
        elif j==i:
            inputinfor[i][i]+=inputinfor[i-1][i-1]
        else:
            inputinfor[i][j]+=max(inputinfor[i-1][j],inputinfor[i-1][j-1])
if lines%2==1:
    print(inputinfor[lines-1][lines//2])
else :
    print(max(inputinfor[lines-1][lines//2],inputinfor[lines-1][lines//2-1]))
