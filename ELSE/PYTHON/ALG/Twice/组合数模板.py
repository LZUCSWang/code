def C1(n,m):#计算组合数
    t=1
    i,j=n,1
    while j<=m:
        t*=i/j
        i-=1
        j+=1
    return int(t)
from math import factorial as f
def C2(n,m):
    return f(n)//(f(n-m)*f(m))
def C3(n,m):
    a1,a2,up,low=1,1,n,1
    while low<=m:
        a1*=up
        a2*=low
        low+=1
        up-=1
    return a1//a2
print(C3(100,50))
print(C1(100,50))
print(C2(100,50))