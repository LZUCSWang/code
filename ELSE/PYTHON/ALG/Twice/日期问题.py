import os
import sys
import datetime
s = input().split('/')
cnt = set()


def slove(y, m, d):
    if int(y) > 59:
        y = '19'+y
    else:
        y = '20'+y
    try:
        t = datetime.date(int(y), int(m), int(d))

        cnt.add(int(y+m+d))
    except:
        return


slove(s[2], s[1], s[0])
slove(s[0], s[1], s[2])
slove(s[2], s[0], s[1])
cnt = list(cnt)
cnt.sort()
for i in range(len(cnt)):
    t = str(cnt[i])
    print("%s-%s-%s" % (t[:4], t[4:6], t[6:]))

# 请在此输入您的代码
