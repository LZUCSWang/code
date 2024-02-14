cnt=set()
import fractions
for i in range(1,2021):
    for j in range(1,2021):
        if i==j or i%j==0:
            continue
        datas=fractions.Fraction(i,j)
        cnt.add(datas)
print(len(cnt))