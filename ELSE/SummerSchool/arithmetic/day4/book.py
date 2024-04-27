n=int(input())
A1,a,b,S=map(int,input().split())
x=(S-A1*n+(n-1)*n//2*b)//(a+b)
y=((n-1)*n//2-x)
print(A1,end=' ')
for i in range(1,n):
    if x<y:
        y-=n-i
        A1-=b
    else:
        A1+=a
        x-=n-i
    print(A1,end='')
    if i!=n-1:
        print(' ',end='')