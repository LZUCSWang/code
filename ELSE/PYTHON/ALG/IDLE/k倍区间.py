#k倍区间
n,k=map(int,input().split())
data=[int(input()) for _ in range(n)]
s=[0]*n
s[0]=data[0]%k

cnt=[0]*k
cnt[s[0]]+=1
for i in range(1,n):
    s[i]+=(s[i-1]+data[i])%k
    cnt[s[i]]+=1


