n = int(input())
data = []
ipt = list(map(int, input().split()))
for i in range(n):
    if ipt[i] != 0:
        if len(data) == 10:
            print("FULL", end='')
            if i == n-1:
                print()
        else:
            data.append(ipt[i])
    else:
        if len(data) == 0:
            print("EMPTY", end='')
            if i == n-1:
                print()
        else:
            print(data.pop(-1), end='')
            if i == n-1:
                print()
print(*data, end='')
