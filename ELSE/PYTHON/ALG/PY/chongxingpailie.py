n = int(input())
data = list(map(int, input().split()))
m = int(input())
ping = [0]*(n+2)
for i in range(1, m+1):
    datas, b = map(int, input().split())
    ping[datas] += 1
    ping[b+1] -= 1
# print(ping)
for i in range(1, n+1):
    ping[i] = ping[i-1]+ping[i]
ping = ping[1:-1]
l = 0
for i in range(n):
    l -= data[i]*ping[i]
ping.sort(reverse=True)
data.sort(reverse=True)
print(data)
# print(ping)
# oign=copy.deepcopy(ping)
for i in range(n):
    l += data[i]*ping[i]
print(l)
