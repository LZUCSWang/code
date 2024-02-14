datas=4380
cnt=0
for i in range(1,4):
    b=int(input())
    print(datas-b)
    print(datas/(datas-b)*i)
    cnt+=datas/(datas-b)*i
print(cnt/3)