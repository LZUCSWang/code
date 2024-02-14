N,K = map(int, input().split())
sts,cnt = [],[]

def is_fit(n):
    for i in range(1,16):
        if n&(1<<i) and n&(1<<(i-1)):
            return False
    return True
    
for i in range(2**N):
    if is_fit(i):
        sts.append(i)
        cnt.append(bin(i).count("1"))
        
cnt = 0
M = len(sts)
dp = [[[0]*(K+1) for _ in range(M)] for _ in range(N)]
for i in range(M):
    dp[0][i][cnt[i]] = 1
    
for i in range(1,N):
    for j in range(M):
        datas = sts[j]
        t1 = cnt[j]
  
        for k in range(M):
            b = sts[k]
            if datas&b or not is_fit(datas|b):continue
            
            for m in range(K+1):
                if m+t1>K:continue
                dp[i][j][t1+m] += dp[i-1][k][m]
        cnt += dp[i][j][K]
        
cnt = 0
for j in range(M):
    cnt += dp[-1][j][K]
print(cnt)