def longestPalindrome(s: str) -> str:
        n=len(s)
        if n<2:
            return s
        maxlen=1
        begin=0
        dp=[[False]*n for _ in range(n)]
        for i in range(n):
            dp[i][i]=True
        for lenth in range(2,n+1):
            for left in range(n):
                right=lenth+left-1
                if right>=n:
                    break
                if s[right]!=s[left]:
                    dp[left][right]=False
                else:
                    if right-left<3:
                        dp[left][right]=True
                    else:
                        dp[left][right]=dp[left+1][right-1]
                if dp[left][right] and right-left+1>maxlen:
                    maxlen=right-left+1
                    begin=left
        return s[begin:begin+maxlen]
print(longestPalindrome('abcbaa'))