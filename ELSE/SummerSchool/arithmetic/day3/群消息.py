n=int(input())
for i in range(n):
    m=int(input())
    data=list(map(int,input().split()))
    maxx=max(data)
    s=sum(data)
    print(maxx*m-s)