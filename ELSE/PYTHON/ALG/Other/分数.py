import fractions
print(fractions.Fraction(2,4))
i=1
cnt=0
for j in range(20):
    cnt+=fractions.Fraction(1,i)
    i*=2
print(cnt)