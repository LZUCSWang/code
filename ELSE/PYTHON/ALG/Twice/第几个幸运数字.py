import os
import sys
# 请在此输入您的代码
from queue import PriorityQueue
number = [3, 5, 7]
q = PriorityQueue()
vis = set()
for every in number:
    q.put((every))
    vis.add(every)

# print(vis)
tot = 0
while not q.empty():
    next_item = q.get()
    for every in number:
        now = next_item * every
        if now not in vis:
            q.put((now))
            vis.add(now)
    tot += 1
    if next_item == 59084709587505:
        print(tot)
        break