n = int(input())
cnt = [1]
def dfs(res):
    if res == 0:
        print('+'.join(map(str, cnt[1:]))
              ) if len(cnt[1:]) != 1 else print('', end='')
        return
    for i in range(cnt[-1], res+1):
        cnt.append(i)
        dfs(res-i)
        cnt.pop(-1)
dfs(n)
