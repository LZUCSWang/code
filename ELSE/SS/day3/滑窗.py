
from collections import deque


def maxslidingwindow(nums, k):

    left = 0
    q = deque()
    for right in range(len(nums)):
        while len(q) > 0 and nums[right] > nums[q[-1]]:
            q.pop()
        q.append(right)
        if q[0] < left:
            q.popleft()
        if right-left+1 >= k:
            print(nums[q[0]], end=' ')
            left += 1


def minslidingwindow(nums, k):

    left = 0
    q = deque()
    for right in range(len(nums)):
        while len(q) > 0 and nums[right] < nums[q[-1]]:
            q.pop()
        q.append(right)
        if q[0] < left:
            q.popleft()
        if right-left+1 >= k:
            print(nums[q[0]], end=' ')
            left += 1


n, k = map(int, input().split())
datas = list(map(int, input().split()))
minslidingwindow(datas, k)
print()
maxslidingwindow(datas, k)
# minslidingwindow

