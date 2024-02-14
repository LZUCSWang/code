n=int(input())
datas=[]
king=tuple(map(int,input().split()))
for i in range(n):
    datas.append(tuple(map(int,input().split())))
datas.sort(key=lambda x:x[0]*x[1])
leftt=king[0]
maxx=0
for i in range(n):
    maxx=max(maxx,leftt//datas[i][1])
    leftt*=datas[i][0]
print(maxx)