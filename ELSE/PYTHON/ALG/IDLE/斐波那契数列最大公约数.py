#斐波那契数列最大公约数
datas,b,c=1,1,0
for i in range(3,2021):
    c=datas+b
    if i==520:
        m=c
    if i==2020:
        n=c
    datas,b,c=b,c,0
from math import gcd
print(gcd(m,n))
