import sys
sys.setrecursionlimit(10000000)

def find(x):
    if last[x] != x:
        last[x] = find(last[x])
    return last[x]
def union(x, y):
    rx, ry = find(x), find(y)
    if rx != ry:
        last[rx] = ry
n = int(input())
last = [i for i in range(n+1)]
data = [[0]*(n+1)]
data += [[0]+list(map(int, input().split())) for _ in range(n)]
# print(data)
edge = []
for i in range(1, n+1):
    for j in range(i+1, n+1):
        edge.append((i, j, data[i][j]))
edge.sort(key=lambda x: x[2])
# print(edge)
cnt = 0
cnt = 0
for item in edge:
    if find(item[0]) != find(item[1]) and cnt < n-1:
        cnt += 1
        cnt += item[2]
        union(item[0], item[1])
print(cnt)
