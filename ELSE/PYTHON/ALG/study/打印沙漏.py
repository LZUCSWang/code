from re import I


i=1
row=input().split()
n=int(row[0])
c=row[1]
while (i+3)//2*(i//2)*2+1<n:
    i+=2
if (i+3)//2*(i//2)*2+1==n:
    cnt=i
    res=0
else:
    cnt=i-2
    res=n-((cnt+3)//2*(cnt//2)*2+1)
flag=1
time=3
for j in range(cnt):
    if j==cnt//2+1:
        flag=0
    if flag==1:
        for k in range(j):
            print(' ',end='')
        for k in range(cnt-j*2):
            print(c,end='')
    else:
        for k in range(cnt-j-1):
            print(' ',end='')
        for k in range(time):
            print(c,end='')
        time+=2
    print()
print(res)
