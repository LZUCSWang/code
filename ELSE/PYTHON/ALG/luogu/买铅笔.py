n=int(input())
data=[list(map(int,input().split())) for _ in range(3)]
m=float('inf')
for i in range(3):
    t=n//data[i][0] if n%data[i][0]==0 else n//data[i][0]+1
    m=min(m,data[i][1]*t)
print(m)