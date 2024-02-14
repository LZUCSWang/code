import sys
def check(start,cha):
    i=1
    while i<=10:
        for j in range(2,int(start**0.5)+1):
            if start%j==0:
                return 0
        start+=cha
        i+=1
    return 1
for start in range(2,10000000):
    for cha in range(2,10000):
        if check(start,cha):
            print(cha)
            sys.exit()
        