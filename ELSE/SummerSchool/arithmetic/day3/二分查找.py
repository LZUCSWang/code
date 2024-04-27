while True:
    n=int(input())
    data=list(map(int,input().split()))
    data.sort()
    m=int(input())
    s=list(map(int,input().split()))
    print(*data)
    for i in range(m):
        try:
            print(data.index(s[i])+1,end=' ')
        except:
            print(0,end=' ')
    print()