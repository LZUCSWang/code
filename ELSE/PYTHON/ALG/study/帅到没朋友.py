pn = int(input())
data = []
for i in range(pn):
    row = input().split()
    mannum = int(row[0])
    data.append(row[1::])
    data[i].append(mannum)
qn = int(input())
quests = list(input().split())
have = set()
hasflag=0
for i in quests:
    flag = 0
    for j in data:
        if i in j and j[-1] > 1:
            flag = 1
            break
    if flag == 0 and i not in have:
        hasflag=1
        have.add(i)
        print(i,end='')
if hasflag==0:
    print("No one is handsome",end='')
