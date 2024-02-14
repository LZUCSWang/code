L=[]
D=[]
T=[]
import math
def dealua(l):
    aveL=sum(l)/len(l)
    cnt=0
    for i in range(len(l)):
        cnt+=(l[i]-aveL)**2
    ua=1.14*((cnt/20)**0.5)
    return ua
def dealub(tag):
    if tag==1:
        return 0.2/(3**0.5)/10
    if tag==2:
        return 0.02/(3**0.5)/10
    if tag==3:
        return ((0.01/(3**0.5))**2+(0.2/(3**0.5))**2)**0.5
def dealus(datas,b):
    return (datas**2+b**2)**0.5
def dealg(avgL,avgd,avgt):
    return 4*(math.pi**2)*(avgL+avgd/2)/(avgt**2)
for i in range(5):
    L.append(float(input("请输入第%d个数字:"%(i+1))))
for i in range(5):
    D.append(float(input("请输入第%d个数字:"%(i+1))))
for i in range(5):
    T.append(float(input("请输入第%d个数字:"%(i+1))))
ual=dealua(L)
ubl=dealub(1)
uad=dealua(D)
ubd=dealub(2)
uat=dealua(T)
ubt=dealub(3)
print(dealub(3))
usl=dealus(ual,ubl)
usd=dealus(uad,ubd)
ust=dealus(uat,ubt)
usT=ust/100
avgl,avgd,avgt=sum(L)/len(L),sum(D)/len(D),sum(T)/len(T)
avgT=avgt/100
g=dealg(avgl/100,avgd/100,avgT)
def ug(usl,avgl,usd,usT,avgT):
    return g*math.sqrt((usl/avgl)**2+(usd/avgl/2)**2+(usT*2/avgT)**2)
print(ug(usl,avgl,usd,usT,avgT))
print(g)
print(ual,uad,uat)
print(ubl,ubd,ubt)
print(usl,usd,ust)
