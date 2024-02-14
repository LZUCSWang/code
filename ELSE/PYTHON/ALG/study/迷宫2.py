from queue import Queue
#          D        L        R      U
flags = [[1, 0], [0, -1], [0, 1], [-1, 0]]


def next_states(_x, _y, row, col):
    res = []
    for (dx, dy) in flags:
        x, y = _x + dx, _y + dy
        if (0 <= x < row and 0 <= y < col) and (maze[x][y] == '0'):
            res.append((x, y))
    return res


def gen_flagection(x1, y1, x2, y2):
    delta_x = x2 - x1
    delta_y = y2 - y1
    if delta_x > 0:
        return 'D'
    if delta_y < 0:
        return 'L'
    if delta_y > 0:
        return 'R'
    if delta_x < 0:
        return 'U'


maze = '''010000
000100
001001
110000'''.split()
row, col = len(maze), len(maze[0])
queue = Queue()

start = (0, 0)
target = (row-1, col-1)

queue.put((0, 0))
pres = {start: start}

while not queue.empty():
    x, y = queue.get()
    if (x, y) == target:
        break
    for (nx, ny) in next_states(x, y, row, col):
        if (nx, ny) not in pres.keys() and maze[nx][ny] == '0':
            queue.put((nx, ny))
            pres[(nx, ny)] = (x, y)

path = []
cur = target
while cur != start:
    path.append(cur)
    cur = pres[cur]
path.append((0, 0))
path = path[::-1]

print(path)

seq = []
for i in range(1, len(path)):
    seq.append(gen_flagection(*path[i-1], *path[i]))
print(''.join(seq))
