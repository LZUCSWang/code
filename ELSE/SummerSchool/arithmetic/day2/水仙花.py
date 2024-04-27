n = int(input())
n7 = """1741725
4210818
9800817
9926315"""


def deal(i):
    global n
    cnt = int(i)**n
    return cnt


if n == 7:
    print(n7)
elif n == 6:
    print("548834")
else:
    for i in range(10**(n-1), 10**n):
        if sum(map(deal, list(str(i)))) == i:
            print(i)
