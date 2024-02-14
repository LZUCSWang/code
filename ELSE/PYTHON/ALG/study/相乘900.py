def check(i, j, k):
    row = set()
    s = str(i)+str(j)+str(k)
    for i in range(10):
        row.add(s[i])
    if len(row) == 10:
        return 1
    return 0
for i in range(1001, 10000):
    for j in range(1000, i):
        for k in range(10, 100):
                if (i-j)*k == 900 and i != 5012 and j != 4987 and k != 36 and check(i, j, k) == 1:
                    print("(%d-%d)*%d" % (i, j, k))
                    break
