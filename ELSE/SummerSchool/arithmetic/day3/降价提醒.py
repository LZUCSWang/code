n,m=map(int,input().split())
for i in range(n):
    t=float(input())
    if t<m:
        print("On Sale! %.1f"%t)