n, m = map(int, input().split())
last = {}
for i in range(n):
    datas, b = map(int, input().split())
    t = datas, b, i+1
    last[t] = t


def find_root(item):
    if last[item] != item:
        last[item] = find_root(last[item])
    return last[item]


def union(item1, item2):
    r1, r2 = find_root(item1), find_root(item2)
    if r1 != r2:
        last[r1] = r2


have = []
for i in range(m):
    datas, b = map(int, input().split())
    for i in last.keys():
        for j in last.keys():
            if i != j and (i[2] == datas and j[2] == b):
                union(i, j)
                have.append(i)
                have.append(j)
graph = []
for i in last.keys():
    if i not in have:
        low = float("inf")
        for j in have:
            low = min(low, ((i[0]-j[0])**2+(i[1]-j[1])**2)**0.5)
            lowtiem = j
        t = i, lowtiem, low
        graph.append(t)
graph.sort(key=lambda x: x[2])
cnt = 0
for i in graph:
    if find_root(i[0]) != find_root(i[1]):
        union(i[0], i[1])
        cnt += i[2]
print("%.2f" % cnt)
