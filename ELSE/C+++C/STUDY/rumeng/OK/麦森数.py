n=int(input())
def quickpow(a,b):
    ans=1
    while b:
        if b&1:
            ans*=a
        a*=a
        b>>=1
    return ans
s=str(quickpow(2,n)-1)
print(len(s))
t=0
if (len(s)>=500):
    for i in range(-500,0):
        print(s[i],end='')
        t+=1
        if t%50==0:
            print()

else:
    s='0'*(500-len(s))+s
    for i in range(-500,0):
        print(s[i],end='')
        t+=1
        if t%50==0:
            print()

    # # print(s)
