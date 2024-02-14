from re import T


n=int(input())
data=[int(input()) for _ in range(n)]
d={2:False,6:False,12:False,4:True,8:True,24:False,72:False}
for i in data:
    if i in d.keys():
        print("yes") if d[i] else print("no")
        continue

