n, m = map(int, input().split())
for i in range(m):
    row = input()
    start = (1+2**n)/2
    for j in range(n):
        if row[j] == 'y':
            start -= (2**(n-j-1))/2
        else:
            start += (2**(n-j-1))/2
    print("%d" % int(start))
