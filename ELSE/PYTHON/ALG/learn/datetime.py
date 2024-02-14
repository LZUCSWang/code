import datetime
t=datetime.date(2019,8,26)
print(type(t))
print(t.day,t.month,t.year)
#<class 'datetime.date'>
#26 8 2019
datas=datetime.date.today()
print(datas)
print(type(datas))
print(str(datas))
print(type(datas))
print(datas.month,datas.day,datas.year)
print(datas-t)
