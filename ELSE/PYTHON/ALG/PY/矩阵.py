n=int(input())
for i in range(n):
    a1,b1,a2,b2,a3,b3=map(int,input().split())
    if a1==a2 and a2==a3:
        print(4)
        continue