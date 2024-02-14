import sys
from collections import deque
start = '123456789'
end = '876543219'
flags = [-2, -1, 1, 2]
queue = deque([(start, 0)])
seen = [False]*999999999
seen[123456789] = True
# import copy
while len(queue):
    item = queue.popleft()
    item, t = item[0], item[1]
    index9 = item.index('9')
    for d in flags:
        copyed = item
        copyed = list(item)
        nextplace = index9+d
        copyed[index9], copyed[(index9+d) %
                               9] = copyed[(index9+d) % 9], copyed[index9]
        sitem = ''.join(copyed)
        if sitem == end:
            # print(1)
            print(t+1)
            # print(len(queue))
            sys.exit()
        nitem = int(sitem)
        if seen[nitem] == False:
            queue.append((sitem, t+1))
            seen[nitem] = True
