import sys
ra, ca = map(int, input().split())
da = []
for i in range(ra):
    da.append(list(map(int, input().split())))
rb, cb = map(int, input().split())
db = []
for i in range(rb):
    db.append(list(map(int, input().split())))
if ca != rb:
    print("Error: %d != %d" % (ca, rb))
    sys.exit()
print(ra, cb)


def jzsum(i, j):
    global ca
    ad, bd, temp = 0, 0, 0
    while ad != ca:
        temp += da[i][ad]*db[bd][j]
        ad += 1
        bd += 1
    return temp


cnt = [[0]*cb for _ in range(ra)]
for i in range(ra):
    for j in range(cb):
        cnt[i][j] = jzsum(i, j)
for i in cnt:
    print(' '.join(map(str, i)))