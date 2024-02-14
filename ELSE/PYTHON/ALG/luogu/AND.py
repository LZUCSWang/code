"""4
5
1 2 2 3 6
3
1 3 1
3
1 2 1
4
3 1 1 2"""
n = int(input())
for test in range(n):
    s, odd = 0, 0
    t = int(input())
    data = list(map(int, input().split()))
    for i in range(1, t-1):
        odd += data[i] % 2
        s += data[i]//2
    if (odd and t == 3) or s==0:
        print(-1)
        continue
    s += odd
    print(s)
