def slove(s1,s2):
    max=0
    m,n=len(s1),len(s2)
    dp=[[0]*(n+1) for _ in range(m+1)]
    for i in range(1,m+1):
        for j in range(1,n+1):
            if s1[i-1]==s2[j-1]:
                dp[i][j]=dp[i-1][j-1]+1
                if max<dp[i][j]:
                    max=dp[i][j]
    print(max)
slove('abefecd','becd')