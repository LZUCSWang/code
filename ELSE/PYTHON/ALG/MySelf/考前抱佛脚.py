numlist = list(map(int, input().split()))
cnt = 0
for i in range(4):
    data = [0]+list(map(int, input().split()))
    data.sort()
    s = sum(data)
    f = [[0]*(s//2+1) for _ in range(numlist[i]+1)]
    for j in range(1, numlist[i]+1):
        for k in range(s//2+1):
            f[j][k] = f[j-1][k]
            if k >= data[j]:
                f[j][k] = max(f[j][k], f[j-1][k-data[j]]+data[j])
    t = max(f[-1])
    cnt += max(t, s-t)
print(cnt)
