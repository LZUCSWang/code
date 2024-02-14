n=2021041820210418
cnt=[]
docker=set()
for i in range(1,int(n**0.5)+1):
    if n%i==0:
        cnt.append(i)
        cnt.append(n//i)
for i in cnt:
    for j in cnt:
        for k in cnt:
            if (i,j,k) not in docker and i*j*k==n:
                docker.add((i,j,k))
print(len(docker))
