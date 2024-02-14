"""x = ["UDDLUULRUL",
     "UURLLLRRRU",
     "RRUURLDLRD",
     "RUDDDDUUUU",
     "URUDLLRRUU",
     "DURLRLDLRL",
     "ULLURLLRDU",
     "RDLULLRDDD",
     "UUDDUDUDLL",
     "ULRDLUURRR"]
res = 0
for i in range(len(x)):
    for j in range(len(x[0])):
        n = [[0]*10 for _ in range(10)]
        datas = i
        b = j
        n[datas][b] += 1
        while n[datas][b] ==1:
            if x[datas][b] == 'U':
                datas -= 1
            elif x[datas][b] == 'D':
                datas += 1
            elif x[datas][b] == 'L':
                b -= 1
            else:
                b += 1
            if (datas<0 or datas >= 10 or b < 0 or b >= 10):
                res +=1
                break
            n[datas][b] += 1
            if n[datas][b] > 1:
                break
print(res)
"""
x = ["UDDLUULRUL",
     "UURLLLRRRU",
     "RRUURLDLRD",
     "RUDDDDUUUU",
     "URUDLLRRUU",
     "DURLRLDLRL",
     "ULLURLLRDU",
     "RDLULLRDDD",
     "UUDDUDUDLL",
     "ULRDLUURRR"]
res = 0
for i in range(len(x)):
    for j in range(len(x[0])):
        n = [[0]*10 for _ in range(10)]
        datas = i
        b = j
        n[datas][b] += 1
        while n[datas][b] == 1:
            if x[datas][b] == "U":
                datas -= 1
            elif x[datas][b] == "D":
                datas += 1
            elif x[datas][b] == "L":
                b -= 1
            else:
                b += 1
            if datas >= 10 or b >= 10 or datas < 0 or b < 0:
                res += 1
                break
            n[datas][b] += 1
            if n[datas][b] > 1:
                break
print(res)
