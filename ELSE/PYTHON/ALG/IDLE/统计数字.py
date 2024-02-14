#统计数字
n=int(input())
data=[int(input()) for _ in range(n)]
data.sort()
cnt=1
for i in range(n):
    if i==n-1:
        if data[i]==data[i-1]:
            print(data[i],cnt)
        else:
            print(data[i],1)
        break
    if data[i]==data[i+1]:
        cnt+=1
    else:
        print(data[i],cnt)
        cnt=1
