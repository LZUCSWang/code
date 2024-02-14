#交易
cnt=0
n=int(input())
data=list(map(int,input().split()))
for i in range(n):
    for j in range(i+1,n):
        cnt=max(cnt,data[j]-data[i])
print(cnt)
