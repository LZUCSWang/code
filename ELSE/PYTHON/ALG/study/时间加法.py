datas=int(input())
b=int(input())
t=int(input())
datas+=(t+b)//60
b=(t+b)%60
print(datas)
print(b)