from collections import deque
n, m = map(int, input().split())
sx, sy = map(int, input().split())
left, right = map(int, input().split())
data = [input() for _ in range(n)]
seen = [[0]*m for _ in range(n)]


def check(nx, ny):
    if nx >= 0 and ny >= 0 and nx < n and ny < m and data[nx][ny] == '.' and seen[nx][ny] == 0:
        seen[nx][ny]=1
        return True
    return False


def bfs(x, y, left, right):
    queue = deque([(x, y, left, right)])
    global cnt
    while len(queue):
        cnt += 1
        item = queue.popleft()
        x, y, ll, rr = item[0], item[1], item[2], item[3]
        if ll > 0:
            nx, ny = x, y-1
            if check(nx, ny):
                queue.append((nx, ny, ll-1, rr))
        if rr > 0:
            nx, ny = x, y+1
            if check(nx, ny):
                queue.append((nx, ny, ll, rr-1))
        nx, ny = x+1, y
        if check(nx, ny):
            queue.append((nx, ny, ll, rr))
        nx, ny = x-1, y
        if check(nx, ny):
            queue.append((nx, ny, ll, rr))


cnt = 0
seen[sx-1][sy-1]=1
bfs(sx-1, sy-1, left, right)
print(cnt)
# for i in range(n):
#     print(seen[i])
