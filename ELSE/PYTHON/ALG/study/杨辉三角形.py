def bianchang(temp,line):
    temp1=[]
    temp1.append(1)
    for i in range(1,line-1):
        temp1.append(temp[i]+temp[i-1])
    temp1.append(1)
    return temp1
data=[]
m=int(input())
line=1
temp=[1]
while m not in data:
    temp=bianchang(temp,line)
    for i in temp:
        data.append(i)
    line+=1
print(data)
print(data.index(m))