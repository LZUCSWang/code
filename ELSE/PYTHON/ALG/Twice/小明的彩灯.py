"""
5 3
2 2 2 1 5
1 3 3
4 5 5
1 1 -100
"""
n,m=map(int,input().split())
data=[0]+list(map(int,input().split()))+[0]
chadata=[0]*(n+2)
for i in range(1,n+2):
    chadata[i]=data[i]-data[i-1]
# print(chadata)
for i in range(m):
    datas,b,c=map(int,input().split())
    chadata[datas]+=c
    chadata[b+1]-=c
    # print(chadata)
# print(chadata)
for i in range(1,n+1):
    chadata[i]=chadata[i]+chadata[i-1]
    if chadata[i]>=0:
        print(chadata[i],end=' ')
    else:
        print(0,end=' ')