
"""data=[1]*20190324
for i in range(3,20190324):
  data[i]=(data[i-1]+data[i-2]+data[i-3])%10000
print(data[-1])"""
datas,b,c,d=1,1,1,0
time=0
while time<20190321:
  d=(datas+b+c)%10000
  datas,b,c=b,c,d
  time+=1
print(d%10000)
# 请在此输入您的代码