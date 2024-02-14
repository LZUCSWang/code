# from curses.ascii import isalpha
import random
data = {}
while True:
    c = input()
    if c == '0':
        print(data)
        break
    datas = input()
    # if datas.isalpha():
    data[c.replace(datas, '_____')] = datas
    # else:
    #     data[datas]=c
right, wrong = set(), set()
# print(len(data))
for sentence in random.sample(data.keys(), len(data)):
    print(sentence)
    ipt = input()
    while True:
        if ipt == data[sentence]:
            right.add(sentence)
            break
        else:
            print("Wrong!Try again!")
            wrong.add(sentence)
            ipt = input()
            if ipt == 'help':
                print(data[sentence])
                ipt = input()
for sentence in wrong:
    print(sentence, data[sentence])
