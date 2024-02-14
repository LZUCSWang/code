yin=[]
cnt=0
for i in range(1,int(2021041820210418**0.5)+1):
    if 2021041820210418%i==0:
        yin.append(i)
        yin.append(2021041820210418//i)
for i in range(len(yin)):
    for j in range(len(yin)):
        for k in range(len(yin)):
            if yin[i]*yin[k]*yin[j]==2021041820210418:
                cnt+=1
print(cnt)