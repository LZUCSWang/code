from collections import deque
maxq = deque([0])
n, m = map(int, input().split())
data = list(map(int, input().split()))
left = 0
for right in range(1, n):
    if right < m-1:
        for j in range(len(maxq)-1, -1, -1):
            if data[maxq[j]] > data[right]:
                maxq.pop()
            else:
                break
        maxq.append(right)
        continue
    """1 3 -1 -1 0 2 -1
        3 3 0 2 2
        """
    if maxq[0] < left:
        maxq.popleft()
    for j in range(len(maxq)-1, -1, -1):
        if data[maxq[j]] > data[right]:
            maxq.pop()
        else:
            break
    maxq.append(right)
    print(data[maxq[0]], end=' ')
    left += 1
maxq.clear()
print()
left = 0

for right in range(1, n):
    if right < m-1:
        for j in range(len(maxq)-1, -1, -1):
            if data[maxq[j]] < data[right]:
                maxq.pop()
            else:
                break
        maxq.append(right)
        continue
    if maxq[0] < left:
        maxq.popleft()
    for j in range(len(maxq)-1, -1, -1):
        if data[maxq[j]] < data[right]:
            maxq.pop()
        else:
            break
    maxq.append(right)
    print(data[maxq[0]], end=' ')
    # cntmax.append(data[maxq[0]])
    left += 1
maxq.clear()
print()
left = 0
