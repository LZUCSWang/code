n = int(input())
data = [input() for _ in range(n)]
flags = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (1, -1), (-1, -1), (-1, 1)]
target = 'yizhong'
amap = [['*']*n for _ in range(n)]


def check(i, j, d):
    global n
    if i+d[0]*6 > n or j+d[1]*6 > n or i+d[0]*6 < 0 or j+d[1]*6 < 0:
        return False
    for k in range(1, 7):
        if data[i+d[0]*k][j+d[1]*k] != target[k]:
            return False
    return True


for i in range(n):
    for j in range(n):
        if data[i][j] == 'y':
            for d in flags:
                if check(i, j, d):
                    for k in range(7):
                        amap[i+d[0]*k][j+d[1]*k] = target[k]
for i in range(n):
    print(''.join(amap[i]))
