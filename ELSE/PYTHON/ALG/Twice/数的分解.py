n = 2019
cnt = 0
for i in range(1, 627):
    for j in range(i+1,1009):
        k=2019-i-j
        if k>j and not ( '2' in str(i)+str(j)+str(k) or '4' in str(i) + str(j) +str(k)):
            cnt+=1
print(cnt)
