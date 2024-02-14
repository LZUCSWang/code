#分巧克力
n,k=map(int,input().split())
data=[tuple(map(int,input().split())) for _ in range(n)]
left,right=0,1000000000
def check(width):
    cnt=0
    for i in range(n):
        cnt+=(data[i][0]//width)*(data[i][1]//width)
    return cnt
while left<=right:
    mid=(left+right)//2
    if check(mid)>=k:
        left=mid+1
    else:
        right=mid-1
print(right)
