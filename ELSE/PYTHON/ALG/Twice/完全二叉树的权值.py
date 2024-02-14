from pickle import TRUE
import sys


n = int(input())
data = list(map(int, input().split()))
i, sumofrange, maxs, flag = 1, 0, 0, 0
while True:
    rang = int(2**(i-1))+sumofrange
    if rang >= n:
        flag = 1
    if flag == 0:
        s = sum(data[sumofrange:rang])
    else:
        s = sum(data[sumofrange:])
    if s > maxs:
        maxs = s
        cnt = i
    if flag == 1:
        print(cnt)
        sys.exit()
    sumofrange = rang
    i += 1
