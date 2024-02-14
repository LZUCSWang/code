import sys


n, datas, b = map(int, input().split())
if datas==b:
    print(0)
    sys.exit()
data = [0]+list(map(int, input().split()))
queue = [(datas, 0)]
seen = [0]*(n+1)
seen[datas]=1
flags = [1, -1]
while len(queue) > 0:
    item = queue.pop(0)
    l, t = item[0], item[1]
    seen[l] = 1
    for i in flags:
        ni = l+i*data[l]
        if ni > 0 and ni <= n and seen[ni] == 0:
            if ni == b:
                print(t+1)
                sys.exit()
            seen[ni] = 1
            queue.append((ni, t+1))
print(-1)
