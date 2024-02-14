#最长回文子串
dp=[]
def longestPalindrome(s):
    if not s:
        return 0
    n=len(s)
    dp=[[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        dp[i][i]=1
    for i in range(n-1):
        if s[i]==s[i+1]:
            dp[i][i+1]=1
    for i in range(n-3,-1,-1):
        for j in range(i+2,n):
            if s[i]==s[j] and dp[i+1][j-1]:
                dp[i][j]=1
    max_len=0
    for i in range(n):
        for j in range(i,n):
            if dp[i][j]==1:
                max_len=max(max_len,j-i+1)
    return max_len
    