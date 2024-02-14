n,m=int(input()),-float('inf')
data=[[0]*n for _ in range(n)]
for i in range(n-1):
    t=list(map(int,input().split()))
    for j in range(1,len(t)+1):
        data[i][j]=t[j-1]
        data[j][i]=t[j-1]