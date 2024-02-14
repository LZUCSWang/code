import sys
n, m, t = map(int, input().split())
data = [0]*(n+1)
dan = [tuple(map(int, input().split())) for _ in range(m)]
dan.sort(key=lambda x: x[0])
seen = [0]*(n+1)
lasttime = 0
for item in dan:
    nowtime = item[0]
    nowdian = item[1]
    if nowtime > t:
        print(sum(seen))
        sys.exit()
    for i in range(lasttime, nowtime):
        for j in range(1, n+1):
            if j != nowdian and data[j] > 0:
                data[j] -= 1
            if seen[j] == 1 and data[j] <= 3:
                seen[j] = 0
    data[nowdian] += 2
    if data[nowdian] > 5:
        seen[nowdian] = 1
    lasttime = nowtime
if lasttime==t:
    print(sum(seen))
    sys.exit()
for i in range(1,n+1):
    if seen[i]==1:
        data[i]-=(t-lasttime)
        if data[i]<=3:
            seen[i]=0
print(sum(seen))

