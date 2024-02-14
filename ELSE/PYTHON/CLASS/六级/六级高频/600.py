import time
import sys
import random
import smtplib
# import pyautogui
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.text import MIMEText


def send_email(msg_from,  msg_to, text_content, file_path=None):
    msg = MIMEMultipart()
    subject = "python 实现邮箱发送邮件"  # 主题
    text = MIMEText(text_content)
    msg.attach(text)
    # docFile = 'C:/Users/main.py'  如果需要添加附件，就给定路径
    if file_path:  # 最开始的函数参数我默认设置了None ，想添加附件，自行更改一下就好
        docFile = file_path
        docApart = MIMEApplication(open(docFile, 'rb').read())
        docApart.add_header('Content-Disposition',
                            'attachment', filename=docFile)
        msg.attach(docApart)
        print('发送附件！')
    msg['Subject'] = subject
    msg['From'] = msg_from
    msg['To'] = msg_to
    try:
        s = smtplib.SMTP_SSL("smtp.qq.com", 465)
        s.login(msg_from, password[msg_from])
        s.sendmail(msg_from, msg_to, msg.as_string())
        print("发送成功")
    except smtplib.SMTPException as e:
        print("发送失败")
    finally:
        s.quit()


fr = '1779222504@qq.com'
to = '2949242759@qq.com'
password = {'1779222504@qq.com': 'lhzxazjmvmhjdfjj',
            '2949242759@qq.com': 'hkummslmigjcdede'}
try:
    n = int(input('输入循环次数：'))
except:
    n = 10
try:
    l = int(input('输入要复习的单词数：'))
except:
    l = 50
fd = open('D:\code\PYTHON\六级高频\data.txt', 'r', encoding='utf-8')
trcnt = {}
datalist = fd.read().split('\n')
# print(datalist)
for i in datalist:
    si = i.split(' ', 1)
    try:
        trcnt[si[0]] = si[1]
    except:
        print(si)
        exit()
f = open('D:\code\PYTHON\六级高频\learned.txt', 'r+')
have = f.read().split()
queue = []
k = 0
buf = []
fk = open('D:\code\PYTHON\六级高频\killed.txt', 'r+')
killed = fk.read().split()
count = l if len(have) > l else len(have)
flag = 1
if count != 0:
    print('复习')
    for i in random.sample(have[len(have)-count:], count):
        if i in queue or i in killed:
            continue
        for j in range(3):
            print(i, trcnt[i])
            # if j != 2:
            # time.sleep(2)
        queue.append(i)
        buf.append(i)
        for j in random.sample(queue, len(queue)):
            if j in killed:
                continue
            print(j, end='\t\t')
            cnt = input()
            if cnt == 'k':
                killed.append(j)
            elif cnt == 'end':
                for item in killed:
                    fk.write(item+'\n')
                sys.exit()
            elif j not in killed:
                print(trcnt[j])
        if len(queue) >= n:
            queue.pop(0)
cnt = 0
for i in random.sample(list(trcnt.keys()), len(trcnt.keys())):
    if i in have or i in queue:
        continue
    cnt += 1
    for j in range(3):
        print(i, trcnt[i], cnt)
        # time.sleep(2)
    buf.append(i)
    queue.append(i)
    # trcnt[si[0]] = si[1]
    for j in random.sample(queue, len(queue)):
        if j in killed:
            continue
        print(j, end='\t\t')
        cnt = input()
        if cnt == 'k':
            killed.append(j)
        elif cnt == 'end':
            # have += buf
            cnt = input('是否输出本次所有单词(%d)' % len(buf))
            if cnt == 'y':
                temp = ''
                for i in buf:
                    temp += i+'  '+trcnt[i]+'\n'
                    print(i, trcnt[i])
                send_email(fr, to, temp)
            for item in buf:
                if item not in have:
                    f.write(item+'\n')
                    # have.append(item)
            for item in killed:
                fk.write(item+'\n')
            sys.exit()
        elif j not in killed:
            print(trcnt[j])
    if len(queue) >= n:
        queue.pop(0)
f.close()
fd.close()
