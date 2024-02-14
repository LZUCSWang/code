import os
import sys
import datetime
start=datetime.date(1900,1,1)
end=datetime.date(9999,12,31)
dta=datetime.timedelta(days=1)
cnt=0
while start!=end:
    if '2' in str(start.day) or '2' in str(start.month) or '2' in str(start.year):
        cnt+=1
    start+=dta
print(cnt+1)
# 请在此输入您的代码