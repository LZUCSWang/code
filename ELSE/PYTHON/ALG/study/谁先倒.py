import sys
second, mb = map(int, input().split())
n = int(input())
ha, hb = 0, 0
for i in range(n):
    hana, huaa, hanb, huab = map(int, input().split())
    if huaa == hana+hanb:
        second -= 1
        ha += 1
        if second==0:
            print("datas")
            print(hb)
            sys.exit()
    if huab == hana+hanb:
        mb -= 1
        hb += 1
        if mb==0:
            print("B")
            print(ha)
            sys.exit()
    if second==0 or mb==0:
        break
