n = int(input())
data = []
for i in range(n):
    datas = input()
    if '_' not in datas:
        j = 0
        while j < len(datas):
            if datas[j].isupper():
                datas = datas[:j]+'_'+datas[j:]
                j += 1
            j += 1
    datas = '_'.join([word.upper() for word in datas.split('_')])
    if datas not in data:
        data.append(datas)
print(len(data))
for i in data:
    print(i)
