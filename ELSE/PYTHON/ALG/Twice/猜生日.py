import os
import sys
import datetime
start=datetime.date(year=2012,month=3,day=12)
d=datetime.timedelta(days=1)
s=''
def check(start):
  global s
  if start.day<10:
    day='0'+str(start.day)
  else:
    day=str(start.day)
  s=str(start.year)+'06'+day
  ins=int(s)
  if ins%2012==0  and ins%12==0:
    return 1
  return 0
while True:
  start-=d
  if start.month==6 and check(start)!=0:
    print(s)
    break