def check(x, y):
    temp = str(a3)+str(a4)
    ss = set()
    for i in range(len(temp)):
        ss.add(temp[i])
    if len(ss) == 10:
        return 1
    return 0


for i in range(9, 30):
    a3 = i**3
    a4 = i**4
    if len(str(a3))==4 and len(str(a4))==6 and check(a3, a4) == 1:
        print(i)
        break
