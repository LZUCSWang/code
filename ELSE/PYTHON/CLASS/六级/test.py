n=int(input())
for i in range(n,0,-1):
    print((str(i)*(i*2-1)).center(n*2-1,' '))
