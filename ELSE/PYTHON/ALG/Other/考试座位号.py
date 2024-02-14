datanum = int(input())
data = []
for i in range(datanum):
    data.append(input().split())
questnum = int(input())
quest = input().split()
for i in quest:
    for j in data:
        if i == j[1]:
            print("%s %s" % (j[0], j[2]))
