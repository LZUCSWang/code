from datetime import date,timedelta
start=date(1901,1,1)
end=date(2001,1,1)
temp=timedelta(days=1)
cnt=0
while start!=end:
  if start.weekday()==0:
    cnt+=1
  start+=temp
print(cnt)
# 请在此输入您的代码