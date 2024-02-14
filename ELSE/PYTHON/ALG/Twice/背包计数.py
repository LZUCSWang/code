n, m = map(int, input().split())
w, v= [0]*10000, [0]*100000
dp = [0]*(m+1)
t = 0
while t < n:
    w[t], v[t], c = map(int, input().split())
    t += 1
    c -= 1
    n += c
    while c > 0:
        w[t], v[t] = w[t-1], v[t-1]
        t += 1
        c -= 1
for i in range(n):
    for j in range(m, w[i]-1, -1):
        dp[j] = max(dp[j-w[i]]+v[i], dp[j])
print(dp[-1])
