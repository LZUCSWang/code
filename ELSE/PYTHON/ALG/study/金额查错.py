import copy


allmon = int(input())
n = int(input())
data = []
for i in range(n):
    data.append(int(input()))
data.sort()
temp = [0]
cnt = []
seen = [0]*n


def dfs(i):
    if i >= n:
        return
    if sum(temp) == allmon:
        c = copy.deepcopy(data)
        while len(temp) > 0:
            c.remove(temp[1])
            temp.remove(temp[1])
        cnt.append(c)
        return
    if sum(temp) > allmon:
        return
    for j in range(i, n):
        if sum(temp)+data[j] <= allmon and seen[j] == 0:
            seen[j] = 1
            temp.append(data[j])
            dfs(i+1)
            temp.pop()
            seen[j] = 0


dfs(0)
print(cnt)
diccnt = set()
for i in cnt:
    i.pop(0)
    temp = tuple(sorted(i))
    diccnt.add(temp)
print(diccnt)
