import sys
flag = [True]*10000000
n = int(input())
cnt = []
for i in range(2, n+1):
    if flag[i]:
        cnt.append(i)
        for k in range(2*i, n+1, i):
            flag[k] = False
datas = 0
if n in cnt:
    print(1)
    sys.exit()
t = int(n**0.5)+10
# print(cnt)
for i in cnt:
    if i > t:
        break
    if n % i == 0:
        # print(i)
        datas += 1
print(datas)
