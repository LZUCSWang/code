"""7
2 -4 3 -1 2 -4 3"""
n = int(input())
data = list(map(int, input().split()))
sum=m=data[0]
for i in range(1,n):
    if sum<0:
        sum=0
    sum+=data[i]
    m=max(m,sum)
print(m)