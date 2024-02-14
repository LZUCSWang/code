import os
import sys
n, m = map(int, input().split())
data = []
for i in range(n):
    data.append(list(map(int, input().split())))


def dfs(hang, lie) -> int:
    if hang <= 0 or lie <= 0:
        return -99999
    if hang==1 and lie==1:
        return data[0][0]
    current = data[hang-1][lie-1]
    lastmax = max(dfs(hang-1, lie), dfs(hang-2, lie), dfs(hang-3, lie), dfs(hang, lie-1), dfs(
        hang-1, lie-1), dfs(hang-2, lie-1), dfs(hang, lie-2), dfs(hang-1, lie-2), dfs(hang, lie-3))
    return lastmax+current

print(dfs(n, m))
