import sys
n, m = map(int, input().split())
data = [[0]*(n+1) for _ in range(n+1)]
# print(data)
for i in range(m):
    datas, b, c = map(int, input().split())
    data[datas][b] = data[b][datas] = c
    # print(datas,b)
    # sys.exit()


def dfs(last, have):
    global cnt
    cnt = max(have, cnt)
    for next in range(1, n+1):
        if data[last][next] > 0 and seen[next] == 0:
            seen[next] = 1
            dfs(next, have+data[last][next])
            seen[next] = 0


mt = 0
for i in range(1, n+1):
    seen = [0]*(n+1)
    seen[i] = 1
    cnt = 0
    dfs(i, 0)
    mt = max(mt, cnt)
print(mt)
