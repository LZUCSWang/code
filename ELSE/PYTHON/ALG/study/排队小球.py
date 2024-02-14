R, G, B = map(int, input().split())
total = R+G+B
cnt = []
cntnum = 0


def check(cnt):
    temp = 1
    lasttemp = 0
    cnt = cnt+[0]
    for i in range(len(cnt)-1):
        if cnt[i] == cnt[i+1]:
            temp += 1
        else:
            if lasttemp >= temp:
                return 0
            lasttemp = temp
            temp = 1
    return 1


def dfs(cnt, R, G, B):
    global cntnum
    if R == 0 and G == 0 and B == 0:
        if check(cnt) == 1:
            cntnum += 1
        return
    if R > 0:
        cnt.append('R')
        dfs(cnt, R-1, G, B)
        cnt.pop()
    if G > 0:
        cnt.append('G')
        dfs(cnt, R, G-1, B)
        cnt.pop()
    if B > 0:
        cnt.append('B')
        dfs(cnt, R, G, B-1)
        cnt.pop()


dfs(cnt, R, G, B)
print(cntnum)
