import time
import sys
import random
try:
    n = int(input('输入循环次数：'))
except:
    n = 10
try:
    l = int(input('输入要复习的单词数：'))
except:
    l = 50
fd = open('D:\code\PYTHON\六级词汇混眼熟基于记忆曲线实现\data.txt', 'r', encoding='utf-8')
trcnt = {}
datalist = fd.read().split('\n')
for i in datalist:
    si = i.split(' ', 1)
    trcnt[si[0]] = si[1]
f = open('D:\code\PYTHON\六级词汇混眼熟基于记忆曲线实现\learned.txt', 'r+')
have = f.read().split()
queue = []
k = 0
buf = []
count = l if len(have) > l else len(have)
flag = 1
if count != 0:
    print('复习')
    for i in random.sample(have[len(have)-count:], count):
        if i in queue:
            continue
        for j in range(3):
            print(i, trcnt[i])
            # if j != 2:
            time.sleep(2)
        queue.append(i)
        buf.append(i)
        for j in random.sample(queue, len(queue)):
            print(j, end='\t\t')
            cnt = input()
            if cnt == 'end':
                sys.exit()
            print(trcnt[j])
        if len(queue) >= n:
            queue.pop(0)

for i in random.sample(list(trcnt.keys()), len(trcnt.keys())):
    if i in have or i in queue:
        continue
    for j in range(3):
        print(i, trcnt[i])
        time.sleep(2)
    buf.append(i)
    queue.append(i)
    # trcnt[si[0]] = si[1]
    for j in random.sample(queue, len(queue)):
        print(j, end='\t\t')
        cnt = input()
        if cnt == 'end':
            # have += buf
            cnt = input('是否输出本次所有单词(%d)' % len(buf))
            if cnt == 'y':
                for i in buf:
                    print(i, trcnt[i])
            for item in buf:
                if item not in have:
                    f.write(item+'\n')
                    # have.append(item)
            sys.exit()
        print(trcnt[j])
    if len(queue) >= n:
        queue.pop(0)
f.close()
fd.close()
