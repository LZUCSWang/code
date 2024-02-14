import os
import sys
import datetime
cnt=0
start=datetime.date(1901,1,1)
end=datetime.date(2001,1,1)
d=datetime.timedelta(days=1)
while start!=end:
    if start.weekday()==1:
        cnt+=1
    start+=d
print(cnt)
# 请在此输入您的代码