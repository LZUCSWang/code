n=int(input())
data=[0]+list(map(int,input().split()))
a,b=map(int,input().split())
if data[a]==0:
    print("ERROR: T[%d] is NULL"%a)
    exit()
if data[b]==0:
    print("ERROR: T[%d] is NULL"%b)
    exit()
if a==b:
    print(a//2,data[a//2])
    exit()
if a>b:
    maxx,minn=a,b
if a<b:
    maxx,minn=b,a
while True:
    while maxx>minn:
        maxx//=2
    while maxx<minn:
        minn//=2
    if maxx==minn:
        print(maxx,data[maxx])
        exit()