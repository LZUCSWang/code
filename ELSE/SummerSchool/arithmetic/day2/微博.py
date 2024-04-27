n=int(input())
hash=[0]*1001
for i in range(n):
    datas=list(map(int,input().split()))[1:]
    for i in datas:
        hash[i]+=1
maxx=0
maxxitem=0
for i in range(1000,-1,-1):
    if maxx<hash[i]:
        maxx=hash[i]
        maxxitem=i
print(maxxitem,maxx)