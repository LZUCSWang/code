from itertools import permutations as p
n = int(input())
iter = [i for i in range(1, n+1)]
for item in p(iter):
    for i in item:
        print("%5d" % i, end='')
    print()
