

n = int(input())
data = list(map(int, input().split()))
m = max(data)
flag = [True]*(m+1)
for i in range(n):
    t = data[i]
    while t != 1:
        if t & 1:
            t = (3*t+1)//2
        else:
            t //= 2
        if t <= m:
            flag[t] = False
data.sort(reverse=True)
for item in data:
    if flag[item]:
        print(item,end=' ')
