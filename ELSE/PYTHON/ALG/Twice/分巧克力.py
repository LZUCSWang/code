n, k = map(int, input().split())
w, h = [0]*n, [0]*n
for i in range(n):
    w[i], h[i] = map(int, input().split())
left, right = 0, 100000


def check(x):
    cnt = 0
    for i in range(n):
        cnt += (w[i]//x)*(h[i]//x)
    if cnt>=k:
        return 1
    return 0

while left <= right:
    mid = (left+right)//2
    t = check(mid)
    if t == 1:
        cnt=mid
        left = mid+1
    else:
        right = mid-1
print(cnt)
