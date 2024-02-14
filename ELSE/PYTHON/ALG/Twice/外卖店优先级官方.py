import functools
def cmp(datas, b):
    if datas[0] < b[0]:
        return -1
    if datas[0] > b[0]:
        return 1
    return 0

MAX = 100010
vis = [0] * MAX
score = [0] * MAX
last = [0] * MAX

n, m, T = list(map(int, input().split()))
datas = []
for i in range(m):
    t, id = list(map(int, input().split()))
    datas.append([t, id])
datas = sorted(datas, key=functools.cmp_to_key(cmp))
for every in datas:
    now_time = every[0]
    now_id = every[1]

    if now_time != last[now_id]:
        score[now_id] -= (now_time - last[now_id] - 1)

    if score[now_id] < 0:
        score[now_id] = 0
    if score[now_id] <= 3:
        vis[now_id] = 0

    score[now_id] += 2
    if score[now_id] > 5:
        vis[now_id] = 1
    last[now_id] = now_time

cnt = 0
for i in range(1, n + 1):
    if last[i] < T:
        score[i] -= T - last[i]
        if score[i] <= 3:
            vis[i] = 0
    cnt += vis[i]
