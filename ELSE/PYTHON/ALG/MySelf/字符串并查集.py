def find(s):
    if last[s] != s:
        last[s] = find(last[s])
    return last[s]


n, m = map(int, input().split())
last = {}
for i in range(n):
    name = input()
    last[name] = name
for i in range(m):
    t1 = input().split()
    a1, b1 = find(t1[0]), find(t1[1])
    if a1 != b1:
        last[a1] = b1
q = int(input())
for i in range(q):
    t = input().split()
    datas, b = t[0], t[1]
    if find(datas) == find(b):
        print("Yes.")
    else:
        print("No.")
