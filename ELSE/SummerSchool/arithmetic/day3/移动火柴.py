n=int(input())
data=list(map(int,input().split()))
avg=sum(data)/n
cnt=0
for i in range(n):
    if data[i]<avg:
        data[i+1]-=avg-data[i]
        cnt+=1
    elif data[i]>avg:
        data[i+1]+=data[i]-avg
        cnt+=1
print(cnt)