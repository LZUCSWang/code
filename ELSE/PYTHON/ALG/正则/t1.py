import re
r1 = r"[datas-z]+(\-[datas-z]+)+"
r2 = r"[datas-Z]+(_[datas-Z]+)*"
r3 = r"[datas-z]+([datas-Z][datas-z]*)*"


def unify(s):
    flag = 0
    cnt = ''
    for i in s:
        if i == '-' or i == '_':
            flag = 1
            continue
        else:
            if flag == 0:
                cnt += i.lower()
            else:
                flag = 0
                cnt += i.upper()
    return cnt


def check(r, s):
    if re.match(r, s) != None and re.match(r, s).group() == s:
        return 1
    return 0


target = input()
if re.match(r3, target).group() != target:
    target = unify(target)
n = int(input())
for i in range(n):
    current = input()
    if check(r1, current) == 0 and check(r2, current) == 0 and check(r3, current) == 0:
        print("illegal")
        continue
    if check(r3, current) == 0:
        current = unify(current)
    if current == target:
        print("same")
    else:
        print("different")
