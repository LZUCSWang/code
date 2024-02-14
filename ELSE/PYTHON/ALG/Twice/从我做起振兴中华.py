
data = [[0, 1, 2, 3, 4], [1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7]]
dp=[[0]*5 for _ in range(4)]
for i in range(4):
    for j in range(5):
        if i==0 :
            dp[i][j]=1
        elif j==0:
            dp[i][j]=1
        else:
            if data[i][j]==data[i-1][j]+1:
                dp[i][j]+=dp[i-1][j]
            if data[i][j]==data[i][j-1]+1:
                dp[i][j]+=dp[i][j-1]
# for i in range(4):
#     print(dp[i])
print(dp[-1][-1])