n,m=map(int ,input().split())
a=[]
for i in range(n+1):
    a.append(int(input()))
def judge(x):
    sum=0
    for i in range(n,0,-1):
        sum=(sum+a[i])*x
    sum+=a[0]
    return sum==0
ans=[]
for i in range(1,m+1):
    if judge(i):
        ans.append(i)
print(len(ans))
if len(ans)!=0:
    for i in range(n):
        print(ans[i])