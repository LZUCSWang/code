import sys
n = int(input())
data = [[] for _ in range(n)]
seen = [0]*n
qdata = list(map(int, input().split()))
if n == 1:
    i = 1
    j = 0
    print("#1")
    while j < qdata[0]*10:
        print(i, end='')
        i += 2
        if (j+1) % 10 == 0:
            print()
        else:
            print('', end=' ')
        j += 1
    sys.exit()
j = 0
for i in range(1, sum(qdata)*10+1):
    if seen.count(0) > 1:
        data[j].append(i)
        if len(data[j]) == qdata[j]*10:
            seen[j] = 1
        j = (j+1) % n
        while seen[j] == 1:
            j = (j+1) % n
    else:
        j = seen.index(0)
        data[j].append(data[j][-1]+2)
for i in range(n):
    print("#%d" % (i+1))
    for j in range(qdata[i]*10):
        print(data[i][j], end='')
        if (j+1) % 10 == 0:
            print()
        else:
            print('', end=' ')
