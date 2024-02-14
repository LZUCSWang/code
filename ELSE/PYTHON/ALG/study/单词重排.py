import os
import sys
s = "LANQIAO"
temp = []
cnt = set()
seen = [0]*7


def dfs(i):
    global temp,seen,cnt,s
    if i >= 7:
        cnt.add(''.join(temp))
        return
    for j in range(7):
        if seen[j] == 0:
            seen[j] = 1
            temp.append(s[j])
            dfs(i+1)
            temp.pop(-1)
            seen[j] = 0


dfs(0)
print(len(cnt))

# 请在此输入您的代码
