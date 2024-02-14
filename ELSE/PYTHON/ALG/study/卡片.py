num=0
for i in range(1,10000):
    num+=str(i).count('1')
    if num==2021:
        print(i)
        break