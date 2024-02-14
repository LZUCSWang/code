from math import gcd

n = int(input())
data = list(map(int, input().split()))
data.sort()
delta = [data[i]-data[i-1] for i in range(1, n)]
cnt = delta[0]
for i in range(1, len(delta)):
    cnt = gcd(cnt, delta[i])
if cnt == 0:
    print(n)
else:
    print((data[-1]-data[0])//cnt+1)
