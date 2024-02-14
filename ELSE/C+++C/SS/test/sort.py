n = int(input())
datas = list(map(int, input().split()))
datas.sort()
print(*datas, end='')
