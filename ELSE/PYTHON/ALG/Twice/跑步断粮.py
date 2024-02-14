import os
import sys
import datetime
start=datetime.date(year=2000,month=1,day=1)
d=datetime.timedelta(days=1)
end=datetime.date(year=2020,month=10,day=2)
cnt=0
while start!=end:
    cnt+=1
    if start.weekday()==0 or start.day==1:
      cnt+=1
    start+=d
print(cnt)
# 请在此输入您的代码