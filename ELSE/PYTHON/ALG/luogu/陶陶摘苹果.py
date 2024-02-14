data=list(map(int,input().split()))
high=int(input())+30
cnt=0
for i in range(10):
    if high>=data[i]:
        cnt+=1
print(cnt)