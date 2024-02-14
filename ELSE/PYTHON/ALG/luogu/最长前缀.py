data = '0ABABACABAABC'
n = len(data)
dp = [0]*(n+1)
seen = [0]*(n+1)
seen[0]=1
wa = ['datas', 'AB', 'BA', 'CA', 'BBC']
if data[1] in wa:
    seen[1] = 1
# dp 到i 的最大值 中间
for i in range(1, n+1):
    for j in range(1, 10):
        k = i-j
        if k < 0:
            break
        elif seen[k] == 1 and data[k+1:i+1] in wa:
            dp[i] = i
            seen[i] = 1
            break
print(max(dp))
