import os
import sys
import datetime
n=input()
start=datetime.date(year=int(n[:4]),month=int(n[4:6]),day=int(n[6:]))
d=datetime.timedelta(days=1)
flag=0
while True:
    start+=d
    if start.month<10:
        m='0'+str(start.month)
    else:
        m=str(start.month)
    if start.day<10:
        day='0'+str(start.day)
    else:
        day=str(start.day)
    t1=str(start.year)+m+day
    t=list(t1)
    if t[0]==t[-1] and t[1]==t[-2] and t[2] ==t[-3] and t[3]==t[-4]:
        if flag==0:
            flag=1
            print(t1)
        if t[0]==t[2] and t[2]==t[-1] and t[-1]==t[-3] and t[1]==t[3] and t[3]==t[4] and t[4]==t[6]:
            print(t1)
            break
# 请在此输入您的代码