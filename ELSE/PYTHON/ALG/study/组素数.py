data=[1,4,9,9]
cnt=0
datas=set()
def check(num):
    for i in range(2,int(num**0.5)+1):
        if num%i==0:
            return 0
    datas.add(num)
    return 1    
for qian in data:
    for bai in data:
        for shi in data:
            for ge in data:
                temp=[qian,bai,shi,ge]
                if temp.count(1)==1 and temp.count(4)==1 and temp.count(9)==2:
                    num=qian*1000+bai*100+shi*10+ge
                    check(num)
print(len(datas))