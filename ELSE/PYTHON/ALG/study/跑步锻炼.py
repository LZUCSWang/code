import datetime
begin=datetime.date(2000,1,1)
end=datetime.date(2020,10,2)
num=0
while begin!=end:
    if begin.day==1 or begin.weekday()==0:
        num+=2
    else:
        num+=1
    begin+=datetime.timedelta(days=1)
print(num)