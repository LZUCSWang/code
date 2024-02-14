n, k = map(int, input().split())
data = list(map(int, input().split()))
cnt = 0
seen = [0]*n
cnt = 0


def check(x):
    if x == 1:
        return False
    for i in range(2, int(x**0.5)+1):
        if x % i == 0:
            return False
    return True


def dfs(i,x):
    global cnt, cnt
    if i > k:
        if check(cnt):
            cnt += 1
        return
    for j in range(x, n):
        if seen[j] == 0:
            seen[j] = 1
            cnt += data[j]
            dfs(i+1,j+1)
            cnt -= data[j]
            seen[j] = 0


dfs(1,0)
print(cnt)
