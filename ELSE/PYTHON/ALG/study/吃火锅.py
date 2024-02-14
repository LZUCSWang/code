i, s, flag = 1, 0, 0
while True:
    row = input()
    if row == '.':
        break
    if "chi1 huo3 guo1" in row:
        if flag == 0:
            start = i
            flag = 1
        s += 1
    i += 1
if flag == 1:
    print(i-1)
    print(start, s)
else:
    print(i-1)
    print("-_-#")
