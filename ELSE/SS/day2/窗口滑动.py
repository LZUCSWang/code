n,k=map(int,input().split())
maxlist,minlist=[],[]
data=list(map(int,input().split()))
for i in range(n-k+1):
    now=data[i:i+k]
    maxlist.append(max(now))
    minlist.append(min(now))
for i in range(n-k+1):
    print("%d "%minlist[i],end='')
print()
for i in range(n-k+1):
    print("%d "%maxlist[i],end='')