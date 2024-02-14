datas=set()
data=[3,5]
cnt=[3,5]
for k in range(5):
    for i in range(len(cnt)):
        for j in range(i,len(cnt)):
            datas.add(cnt[i]*cnt[j])
    cnt.extend(list(datas))
print(cnt)
print(datas)