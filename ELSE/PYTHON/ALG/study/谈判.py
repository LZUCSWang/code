n = int(input())
cost = 0
data = list(map(int, input().split()))
while len(data) > 1:
    data.sort()
    cost += data[0]+data[1]
    data[1] += data[0]
    data.pop(0)
print(cost)
