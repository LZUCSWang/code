n, m, p = map(int, input().split())
last = [i for i in range(n+1)]


def find_root(x):
    if x != last[x]:
        last[x] = find_root(last[x])
    return last[x]


def union(x, y):
    x_root, y_root = find_root(x), find_root(y)
    if x_root != y_root:
        last[x_root] = y_root


for i in range(m):
    datas, b = map(int, input().split())
    union(datas, b)
for i in range(p):
    datas, b = map(int, input().split())
    if find_root(datas) == find_root(b):
        print("Yes")
    else:
        print("No")
