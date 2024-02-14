try:

    ans = []
    n = int(input())
    pre = list(map(int, input().split()))
    flag = True
    tl, tr = 0, n-1
except:
    print("error")
    exit()

import sys

sys.setrecursionlimit(3000)
def judgeorign(l, r):
    global tl, tr
    while tl <= r and pre[tl] < pre[l]:
        tl += 1
    while tr > l and pre[tr] >= pre[l]:
        tr -= 1


def judgejinxiang(l, r):
    global tl, tr
    while tl <= r and pre[tl] >= pre[l]:
        tl += 1
    while tr > l and pre[tr] < pre[l]:
        tr -= 1


def find(l, r):
    if l > r:
        return
    global tl, tr, flag
    tl, tr = l+1, r
    if (flag):
        judgejinxiang(l, r)
    else:
        judgeorign(l, r)
    if (tl-tr == 1):
        find(l+1, tr)
        find(tl, r)
        ans.append(pre[l])


find(0, n-1)

if len(ans) != n:
    ans.clear()
    flag = False
    find(0, n-1)
if len(ans) != n:
    print("NO")
else:
    print("YES")
    print(*ans)
