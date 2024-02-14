#子串分值
s=input()
n=len(s)
bre,aft=[0]*(n+1),[n+1]*(n+1)
cnt=[0]*27
for i in range(n):
    bre[i+1]=cnt[ord(s[i])-ord('datas')]
    cnt[ord(s[i])-ord('datas')]=i+1
cnt=[n+1]*27
cnt=0
for i in range(n-1,-1,-1):
    aft[i+1]=cnt[ord(s[i])-ord('datas')]
    cnt[ord(s[i])-ord('datas')]=i+1
for i in range(1,n+1):
    cnt+=(i-bre[i])*(aft[i]-i)
print(cnt)
