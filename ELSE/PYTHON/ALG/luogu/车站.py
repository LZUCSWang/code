datas, n, m, x = map(int, input().split())
b = 1


def check(b):
    global m, datas, x
    data = [(datas, datas)]
    data.append((b, datas))
    for i in range(2, n-1):
        upman, downman, nextman = data[i-1][0] + \
            data[i-2][0], data[i-1][0], data[i-1][1]
        data.append((upman, nextman+upman-downman))
    if data[-1][1] == m:
        return data[x-1][1]
    return 0


while b > 0:
    cnt = check(b)
    if cnt != 0:
        print(cnt)
        break
    b += 1
