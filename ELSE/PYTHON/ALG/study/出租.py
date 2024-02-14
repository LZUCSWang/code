n = input()
data = []
for i in range(len(n)):
    if n[i] not in data:
        data.append(n[i])
data.sort(reverse=True)
indexx = []
for i in n:
    indexx.append(data.index(i))
print("int[] arr = new int[]", end='')
s = ''
s += '{'
for i in range(len(data)):
    s += data[i]
    if i != len(data)-1:
        s += ','
s += '};'
print(s)
print("int[] index = new int[]", end='')
t = '{'
for i in range(len(indexx)):
    t += str(indexx[i])
    if i != len(indexx)-1:
        t += ','
t += '};'
print(t, end='')
