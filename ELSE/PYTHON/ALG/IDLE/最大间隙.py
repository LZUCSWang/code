#最大间隙
n=int(input())
data=list(map(int,input().split()))
cnt=0
for i in range(n-1):
    cnt=max(cnt,data[i+1]-data[i])
print(cnt)
