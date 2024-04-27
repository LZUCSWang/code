n=int(input())
for i in range(n):
    datas=input()
    if sum(map(int,list(datas[:3])))==sum(map(int,list(datas[3:]))):
        print("You are lucky!")
    else:
        print("Wish you good luck.")    