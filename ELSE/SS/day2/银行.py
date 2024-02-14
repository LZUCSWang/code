"""8 2 1 3 9 4 11 13 15"""
ipt = list(map(int, input().split()))
n = ipt[0]
ipt = ipt[1:]
datas, B = [], []
for i in range(n):
    if ipt[i] & 1:
        datas.append(ipt[i])
    else:
        B.append(ipt[i])
# print(datas,B)
j, k = 0, 0
for i in range(1, max(len(datas), len(B)*2)+1):
    if i & 1:
        if len(datas) != 0 and j < len(datas):
            print(datas[j], end='')
            if k+j != n-1:
                print(' ', end='')
            j += 1
    else:
        if len(datas) != 0 and j < len(datas):
            print(datas[j], end='')
            if k+j != n-1:
                print(' ', end='')
            j += 1
        if len(B) != 0 and k < len(B):
            print(B[k], end='')
            if k+j != n-1:
                print(' ', end='')
            k += 1
