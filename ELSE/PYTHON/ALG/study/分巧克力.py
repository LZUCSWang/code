def check(x):
    global n
    sum=0
    for i in range(n):
        sum+=(width[i]//x)*(lenth[i]//x)
    return sum
n,k=map(int,input().split())
width,lenth=[],[]
for i in range(n):
    w1,l1=map(int,input().split())
    width.append(w1)
    lenth.append(l1)
l,r=1,max(*width,*lenth)
while l<r:
    mid=(l+r)//2+1
    if check(mid)<k:
        r=mid-1
    else:
        l=mid
print(l)
