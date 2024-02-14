import sys
from collections import deque
datas, b = map(int, input().split())
if datas == b:
    print(0)
    sys.exit()
queue = deque([(datas, 0)])
method = (1, -1, 5, -5, 10, -10)
seen = [False]*1000000
while len(queue):
    item = queue.popleft()
    now, cnt = item[0], item[1]
    for step in method:
        next = now+step
        if next == b:
            print(cnt+1)
            sys.exit()
        if not seen[next]:
            seen[next] = True
            queue.append((next, cnt+1))
