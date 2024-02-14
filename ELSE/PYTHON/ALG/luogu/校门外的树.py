l,m=map(int,input().split())
data=[]
data.append(list(map(int,input().split())))
for i in range(1,m):
    tempx,tempy=map(int,input().split())
    if tempy<data[-1][0] or tempx>data[-1][1]:
        data.append([tempx,tempy])
    elif tempx>=data[-1][0] and tempy<=data[-1][1]:
        continue
    else:
        data[-1][0]=min(tempx,data[-1][0])
        data[-1][1]=max(tempy,data[-1][1])
cnt=l+1
for i in range(len(data)):
    cnt-=data[i][1]-data[i][0]+1
print(cnt)