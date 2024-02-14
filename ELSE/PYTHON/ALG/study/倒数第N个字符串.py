l, n = map(int, input().split())
data = '0abcdefghijklmnopqrstuvwxyz'
print(len(data))
cnt = 26**l-n
cntt=[]
while l > 0:
    l-=1
    t=cnt%26 if cnt%26!=0 else 26
    print(t)
    cntt.append(data[t])
    cnt //= 26
print(cntt)
