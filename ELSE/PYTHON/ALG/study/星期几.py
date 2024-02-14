import datetime
cnt=0
start=datetime.date(1949,10,1)
end=datetime.date(2012,10,1)
d=datetime.timedelta(days=1)
while start!=end:
    start+=d
    if start.month==10 and start.day==1 and start.weekday()==6:
        cnt+=1
print(cnt)