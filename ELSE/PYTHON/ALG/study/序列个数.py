cnt = 0
seen = [0]*11


def dfs(i, j):
    global cnt
    if i > 5:
        cnt += 1
        return
    for k in range(j, 11):
        dfs(i+1, k+1)


dfs(1, 1)
print(cnt)
