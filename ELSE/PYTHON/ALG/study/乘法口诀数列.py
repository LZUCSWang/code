datas, b, n = map(int, input().split())
data = [datas, b]
i = 0
if n == 1:
    print(data[0])
else:
    while len(data) < n:
        data += list(map(int, list(str(data[i]*data[i+1]))))
        i += 1
    print(' '.join(list(map(str, data[:n]))))
