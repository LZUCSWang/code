import sys
datas, b, c, m = map(int, input().split())
#a层b行c列
data = [[[0]*(c+1) for _ in range(b+1)] for _ in range(datas+1)]
xie = [0]+list(map(int, input().split()))
h = 0
for i in range(1, datas+1):
    for j in range(1, b+1):
        for k in range(1, c+1):
            data[i][j][k] = xie[h]
            h += 1
for i in range(m):
    al, ar, bl, br, cl, cr, hurt = map(int, input().split())
    for i in range(1, datas+1):
        if i >= al and i <= ar:
            for j in range(1, b+1):
                if j >= bl and j <= br:
                    for k in range(1, c+1):
                        if k >= cl and k <= cr:
                            data[i][j][k] -= hurt
                            if data[i][j][k] < 0:
                                print(i+1)
                                sys.exit()
