#最大正方形
n,m=map(int,input().split())
data=[['0']*(m+1)]
data+=[['0']+input().split() for _ in range(n)]
dp=[[0]*(m+1) for _ in range(n+1)]
cnt=0
for i in range(1,n+1):
    for j in range(1,m+1):
        if data[i][j]=='1':
            dp[i][j]=1
            cnt=max(cnt,1)
            if data[i-1][j-1]=='1':
                t=dp[i-1][j-1]
                flag1=True
                for row in range(i-t,i):
                    if data[row][j]=='0':
                        flag1=False
                        break
                if  not flag1:
                    break
                for col in range(j-t,j):
                    if data[i][col]=='0':
                        flag1=False
                        break
                if flag1:
                    dp[i][j]=dp[i-1][j-1]+1
                    cnt=max(cnt,dp[i][j])
                """if i==3 and j==3:
                    for i in range(1,n+1):
                        print(dp[i][1:])

                    mm=input()"""
"""for i in range(1,n+1):
    print(dp[i][1:])"""
print(cnt)
