import os
import sys
wid, hei, count = 2019, 324, 0
while wid != hei:
    wid = wid-hei
    if wid < hei:
        wid, hei = hei, wid
    count += 1
print(count+1)
# 请在此输入您的代码
