data = []
cord = [0]*6+[10000, 36, 720, 360, 80, 252, 108, 72, 54,
              180, 72, 180, 119, 36, 306, 1080, 144, 1800, 3600]


def deal(s):
    t = [0]*10
    for i in range(3):
        for j in range(3):
            if data[i][j] == 0:
                x, y = i, j
            t[data[i][j]] = 1
    data[x][y] = t.index(0)


for i in range(3):
    data.append(list(map(int, input().split())))
deal(data)
for i in range(3):
    x, y = map(int, input().split())
    print(data[x-1][y-1])
flags = int(input())
if flags <= 3:
    t = sum(data[flags-1])
elif flags <= 6:
    t = data[0][flags-4]+data[1][flags-4]+data[2][flags-4]
elif flags == 7:
    t = data[0][0]+data[1][1]+data[2][2]
else:
    t = data[0][2]+data[1][1]+data[2][0]
print(cord[t])
