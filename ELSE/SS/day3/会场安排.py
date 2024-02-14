n = int(input())
BE, EN = [0]*(n+1), [0]*(n+1)
for i in range(1, n+1):
    BE[i], EN[i] = map(int, input().split())
BE.sort()
EN.sort()
k = 1
cnt = 0
for i in range(1, n+1):
    if EN[k] <= BE[i]:
        k += 1
        continue
    cnt += 1
print(cnt)
