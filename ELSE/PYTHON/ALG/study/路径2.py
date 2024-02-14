parent = [i for i in range(2022)]
print(parent)


def find_parent(x):
    if x != parent[x]:
        parent[x] = find_parent(x)
    return parent[x]


def union(x, y):
    x_root, y_root = find_parent(x), find_parent(y)
    if x_root != y_root:
        parent[x_root] = y_root


def lcm(x, y):
    pass


edge = [(i, j, lcm(i, j)) for i in range(1, 2022) for j in range(1, 2022)]
j=0
cnt=0
for i in edge:
    if find_parent(i[0])!=find_parent(i[1]) and j<2021:
        j+=1
        union(i[0],i[1])
        cnt+=i[2]

