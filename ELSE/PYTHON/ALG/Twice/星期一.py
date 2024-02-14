import datetime
start=datetime.date(1901,1,1)
end=datetime.date(2000,12,31)
dt=datetime.timedelta(days=1)
cnt=0
while start<=end:
    if start.weekday()==0:
        cnt+=1
    start+=dt
print(cnt)