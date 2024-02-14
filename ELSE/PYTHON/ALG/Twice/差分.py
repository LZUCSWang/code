n, m = map(int, input().split())
data = [0]*(n+2)
for i in range(m):
    datas, b, c = map(int, input().split())
    data[datas] += c
    data[b+1] -= c
for i in range(1, n+1):
    data[i] = data[i]+data[i-1]
print(sum(data[:n+1]))
