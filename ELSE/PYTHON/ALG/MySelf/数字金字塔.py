n = int(input())
data = [int(input())]
for i in range(2, n+1):
    temp = list(map(int, input().split()))
    for j in range(i):
        if j == 0:
            temp[j] += data[0]
        elif j == i-1:
            temp[j] += data[-1]
        else:
            temp[j] += max(data[j], data[j-1])
    data = temp
print(max(data))
