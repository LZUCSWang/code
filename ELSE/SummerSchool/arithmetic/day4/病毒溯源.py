import queue
max_long = 0
n = int(input())
father = [0]*(n+1)
dutt = [0]*(n+1)
graph = [[] for i in range(n+1)]
q = queue.Queue()
for i in range(n):
    temp = list(map(int, input().split()))
    for j in range(1, len(temp)):
        father[temp[j]] = i
        dutt[j] += 1
        graph[i].append(temp[j])
    graph[i].sort()
# 确定起点
for i in range(n):
    if father[i] == 0:
        start = i
        break
q.put((start, 1))
end_pos = start
while not q.empty():
    temp = q.get()
    if temp[1] > max_long:
        max_long = temp[1]
        end_pos = temp[0]
    for i in graph[temp[0]]:
        q.put((i, temp[1]+1))
last_ans = []
while end_pos != start:
    # print(end_pos, end=' ')
    last_ans.append(end_pos)
    end_pos = father[end_pos]
print(max_long)
print(start, end='')
if len(last_ans) != 0:
    print(' ', end='')
    print(*last_ans[::-1])
