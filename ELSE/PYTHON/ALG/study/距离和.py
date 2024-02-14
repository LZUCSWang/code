s="LANQIAO"
data="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
cnt=0
for i in range(len(s)-1):
    for j in range(i+1,len(s)):
        cnt+=abs(data.index(s[i])-data.index(s[j]))
print(cnt)