n=2021041820210418
yin=[]
for item in range(1,int(n**0.5)+1):
    if n%item==0:
      yin.append(item)
      yin.append(n//item)
yin.sort()
cnt=0
for i in yin:
    for j in yin:
        k=n//(i*j)
        if i*j*k==n:
            cnt+=1
print(cnt)
