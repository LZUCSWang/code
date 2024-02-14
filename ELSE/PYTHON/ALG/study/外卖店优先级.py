import os
import sys
n, m, t = map(int, input().split())
dt = [tuple(map(int, input().split())) for _ in range(m)]
dt.sort(key=lambda x: x[0])
cnt = [0]*(m+1)
i = 0
queue = []


def dealjian(c):
    return c-1 if c-1 >= 0 else 0


for tim in range(1, t+1):
    seen = [0]*(m+1)
    while tim == dt[i][0]:
        seen[dt[i][1]] = 1
        cnt[dt[i][1]] += 2
        if cnt[dt[i][1]] == 6:
            queue.append(dt[i][1])
        i += 1
        if i == t:
            break
    for j in range(1, t+1):
        if seen[j] == 0:
            cnt[j] = cnt[j]-1 if cnt[j]-1 >= 0 else 0
            if cnt[j] <= 3 and j in queue:
                queue.remove(j)

print(len(queue))


# 请在此输入您的代码
