n = int(input())
data = list(map(int, input().split()))
i = 0
cnt = 0
temp = 1
for i in range(n-1):
    if data[i] == data[i+1]-1:
        temp += 1
    else:
        cnt = max(temp, cnt)
        temp = 1
print(max(cnt, temp))
