data = list(map(int, input().split()))
data.sort()
for i in range(3):
    print("%d" % data[i], end='')
    if i != 2:
        print("->", end='')
