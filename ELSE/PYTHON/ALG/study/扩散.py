cnt=0
for i in range(-10000,10000):
    for j in range(-10000,10000):
        if abs(i-0)+abs(j-0)<=2020 or abs(i-2020)+abs(j-11)<=2020 or abs(i-11)+abs(j-14)<=2020 or abs(i-2000)+abs(j-2000)<=2020:
            cnt+=1
print(cnt)