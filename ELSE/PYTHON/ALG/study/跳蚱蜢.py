import copy
import sys
start = 123456789
end = 876543219
visited = [0]*999999999
visited[start] = 1
queue = []
queue.append((start, 1))
flags = [-2, -1, 1, 2]
while len(queue) > 0:
    it = queue.pop(0)
    item = it[0]
    step = it[1]
    p0 = str(item).index('9')
    i = list(str(item))
    for flag in flags:
        temp = copy.deepcopy(i)
        temp[p0], temp[(p0+flag+9) % 9] = temp[(p0+flag+9) % 9], temp[p0]
        ni = int(''.join(temp))
        if visited[ni] == 0:
            if ni == end:
                print(step)
                sys.exit()
            visited[ni] = 1
            queue.append((ni, step+1))
