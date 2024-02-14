n, m, p, q = map(int, input().split())  # 学生数，课程数，选课记录数，查询数
dstu = []
dstunum = []
for i in range(n):
    dstu.append(input().split())
dstu.sort(key=lambda x: int(x[0]))
for i in range(n):
    dstunum.append(dstu[i][0])
dclass = []
dclassnum = []
for i in range(m):
    dclass.append(input().split())
dclass.sort(key=lambda x: int(x[0]))
for i in range(m):
    dclassnum.append(dclass[i][0])
dchoice = []
for i in range(p):
    dchoice.append(input().split())
for i in range(q):
    t = input()
    tl = []
    flag = 0
    if t in dstunum:
        for choice in dchoice:
            if choice[0] == t:
                flag = 1
                tl.append(choice[1])
        if flag == 0:
            print("No Data")
            continue
        for i in dclass:
            if i[0] in tl:
                print(' '.join(i))
    elif t in dclassnum:
        for choice in dchoice:
            if choice[1] == t:
                flag = 1
                tl.append(choice[0])
        if flag == 0:
            print("No Data")
            continue
        for i in dstu:
            if i[0] in tl:
                print(' '.join(i))
    else:
        print("Illegal ID")
