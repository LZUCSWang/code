n, m = map(int, input().split())
last = [i for i in range(n+1)]
data = [tuple(map(int, input().split())) for _ in range(m)]
data.sort(key=lambda x: x[2])
cnt = 0
t = 0


def find_root(x):
    if x != last[x]:
        last[x] = find_root(last[x])
    return last[x]


def union(x, y):
    x_root, y_root = find_root(x), find_root(y)
    if x_root != y_root:
        last[x_root] = y_root


for item in data:
    datas, b = item[0], item[1]
    if find_root(datas) != find_root(b):
        union(datas, b)
        cnt += item[2]
        t += 1
if t < n-1:
    print("orz")
else:
    print(cnt)
