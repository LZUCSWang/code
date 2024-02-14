n, m = map(int, input().split())
k, p = list(map(int, input().split())), list(map(int, input().split()))
for i in range(n):
    item = p[i]/k[i], k[i], p[i]
    k[i] = item
cnt = 0
j = 0
k.sort(key=lambda x: x[0], reverse=True)
while m > 0 and j<n:
    if m==k[j][1]:
        cnt+=k[j][2]
        break
    if m >k[j][1]:
        cnt += k[j][2]
        m -= k[j][1]
        j += 1
    else:
        cnt += k[j][0]*m
        break
print("%.2f" % cnt)
