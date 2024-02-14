n=int(input())
data=[]
cnt=0
time=0
for i in range(n):
    datas,b,left=map(int,input().split())
    data.append((datas+b,left))
data=sorted(data,key=lambda x:x[0])
for i in range(n):
    time+=data[i][0]
    cnt+=time
    time+=data[i][1]
print(cnt)

# 请在此输入您的代码