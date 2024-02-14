cnt=0
for i in range(1,2021):
    temp=str(i)
    for j in range(len(temp)):
        if temp[j]=='2':
            cnt+=1
print(cnt)