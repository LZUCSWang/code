import random
import time
f = open('D:\code\PYTHON\史纲\\add.txt', 'r', encoding='utf-8')
# temp=''
dic = {}
queslist = []
try:
    n = int(input("how many?"))
except:
    n = 100
try:
    speed = float(input("speed?"))
except:
    speed = 0
while n:
    ques = f.readline()
    if ques == "END":
        break
    if ques == '\n':
        continue
    temp = ''
    queslist.append(ques)
    n -= 1
    while True:
        cnt = f.readline()
        if cnt == '\n':
            dic[ques] = temp
            break
        temp += cnt
random.shuffle(queslist)
q = []


def shucu(i):
    print(queslist[i], end='')
    datas = input()
    if datas == 'k':
        return False
    if datas == 's':
        return True
    if speed == 0:
        print(dic[queslist[i]])
    else:
        j = 0
        cnt = dic[queslist[i]]
        while j < len(cnt):
            print(cnt[j], end='')
            j += 1
            time.sleep(speed)
    datas = input()
    if datas == 'k':
        return False
    if datas == 's':
        return True
    return True


for i in range(len(queslist)):
    if shucu(i):
        q.append(i)
    if len(q) >= 3:
        shucu(q.pop(0))
