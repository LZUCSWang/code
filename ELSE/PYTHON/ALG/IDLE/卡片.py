#卡片
cnt=0
for i in range(10000000000):
    cnt+=str(i).count('1')
    if cnt==2021:
        print(i)
        break
    if cnt >2021:
        print(i-1)
        break
    
    
