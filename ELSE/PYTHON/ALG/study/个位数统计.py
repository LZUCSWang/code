n = str(input())
j = 0
data = {}
for i in range(10):
    data[i] = j
for i in range(10):
    if n.count(str(i)) != 0:
        data[i] = n.count(str(i))
for i in data.keys():
    if data[i] != 0:
        print("%d:%d" % (i, data[i]))
