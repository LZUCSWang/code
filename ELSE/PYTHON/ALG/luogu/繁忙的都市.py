n, m = map(int, input().split())
edge = [tuple(map(int, input().split())) for _ in range(m)]
edge.sort(key=lambda x: x[2])
last = [i for i in range(n+1)]


def find(x):
    if last[x] != x:
        last[x] = find(last[x])
    return last[x]


def union(x, y):
    rx, ry = find(x), find(y)
    if rx != ry:
        last[rx] = ry


cnt = 0
cnt = -float('inf')
for item in edge:
    if find(item[0]) != find(item[1]) and cnt < n-1:
        union(item[0], item[1])
        cnt += 1
        cnt = max(cnt, item[2])
print(cnt, cnt)
