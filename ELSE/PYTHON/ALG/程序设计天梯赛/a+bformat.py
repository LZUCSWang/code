datas,b=map(int,input().split())
cnt=str(datas+b)
flag1=False
if cnt[0]=='-':
    flag1=True
    cnt=cnt[1:]
flag=0
for i in range(1,len(cnt)):
    t=i
    if t%3==0:
        t=i+flag
        flag+=1
        cnt=cnt[:-t]+','+cnt[(-t):]
if flag1:
    cnt='-'+cnt
print(cnt)
