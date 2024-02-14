import datetime
import sys
d=datetime.timedelta(days=1)
s=input()
start=datetime.date(int(s[:4]),int(s[4:6]),int(s[6:]))
flag=True
def check(st):
    left,right=0,len(st)-1
    while left<right:
        if st[left]!=st[right]:
            return False
        left,right=left+1,right-1
    return True
def check2(start):
    if st[0]==st[2] and st[2]==st[5] and st[5]==st[7] and st[1]==st[3] and st[3]==st[4] and st[4]==st[6]:
        return True
    return False
start=datetime.date(int(s[:4]),int(s[4:6]),int(s[6:]))
while True:
    start+=d
    st=''.join(start.isoformat().split('-'))
    if check(st):
        if flag:
            print(st)
            flag=False
        if check2(st):
            print(st)
            sys.exit()
