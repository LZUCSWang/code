"""n = int(input())
s = input()
seen = [0]*n
datas = []
for i in range(n):
    if s[i] == 'w' or seen[i] == 1:
        continue
    cnt = 0
    t = i
    while t < n and (s[t] == s[i] and seen[t] == 0 or s[t] == 'w'):
        seen[t] = 1
        cnt += 1
        t += 1
    t = i-1
    while t >= -n and (s[i] == s[t]  and seen[t] == 0 or s[t] == 'w'):
        seen[t] = 1
        cnt += 1
        t -= 1
    datas.append(cnt)
if len(datas) == 1:
    print(datas[0])
else:
    m = 0
    for i in range(len(datas)-1):
        m = max(m, datas[i]+datas[i+1], datas[i]+datas[i-1])
    print(m)
"""
n = int(input())
s = input()


def init(i):
    t = s[:i]
    return s[i:]+t

import sys
for i in range(1, n):
    t = init(i)
    left, right = 0, 0
    lp, rp = 0, n-1
    m = 0
    while t[lp]=='w':
        left+=1
        lp+=1
    while lp<n and (t[lp] == 'w' or t[lp] == t[0]):
        if lp==n-1:
            print(n)
            sys.exit()
        lp += 1
        left += 1
    while t[rp]=='w':
        right+=1
        rp-=1
    while rp >=0 and (t[rp] == 'w' or t[rp] == t[-1]):
        rp -= 1
        right += 1
    m = max(m, left+right)
print(min(m,n))
print(init(2))
