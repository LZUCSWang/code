from fractions import Fraction as F
cnt=F(1,1)
for i in range(1,20):
    cnt+=F(1,int(2**i))
print(cnt)
