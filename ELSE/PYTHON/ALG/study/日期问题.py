import sys
x,y,z=map(int,input().split('/'))
cnt=[]
mon=[0,31,28,31,30,31,30,31,31,30,31,30,31]
def run(x):
    if x%4==0 and x%100:return True
    if x%100==0 and x%400==0:return True
    return False
def check(x,y,z):
    if x<60:xx=2000+x
    else:xx=1900+x
    if run(xx):
        mon[2]+=1
        if z<=mon[y]:cnt.append((xx,y,z))
        mon[2]-=1
    else:
        if z<=mon[y]:cnt.append((xx,y,z))
#nyr
if  0<y<=12 and 0<z<=31:check(x,y,z)
#yrn
if 0<x<=12 and 0<y<=31:check(z,x,y)
#ryn
if 0<y<=12 and 0<x<=31:check(z,y,x)
cnt.sort()
cnt=list(dict.fromkeys(cnt))
for x in cnt:
    print("{:04}-{:02}-{:02}".format(x[0],x[1],x[2]))
