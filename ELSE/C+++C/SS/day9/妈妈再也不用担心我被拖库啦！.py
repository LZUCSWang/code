"""
5
R IronMan 1234qwerasdf
R IronMan whejrdfs345
L IronMan 1234qwerasdf
L IronMan whejrdfs345
L IronMan 0km6trlhdcwc
"""


datas = {}
hashs = {}


def get_word_val(word):
    if word.isdigit():
        return int(word)
    return ord(word.lower())-ord('a')+10


def get_str(num):
    return chr(num-10+ord('a'))


def get_hashval(password):
    len_password = len(password)
    ave = len_password//4
    res = len_password % 4
    last_pos, now_pos = 0, 0
    hashval = ""
    flag = True
    for i in range(4):
        if i < res and flag:
            ave += 1
            flag = False
        if i >= res and not flag:
            ave -= 1
            flag = True
        now_pos += ave
        temp = sum(map(get_word_val, password[last_pos:now_pos])) % 36
        if temp < 10:
            hashval += str(temp)
        else:
            hashval += get_str(temp)
        last_pos = now_pos
    # sum(map(get_word_val, password))
    return hashval


def register(name, password):
    if name in datas.keys():
        print("Repeated!")
    else:
        datas[name] = password
        hashs[password] = get_hashval(password)
        print("Signed!")


def login(name, password):
    if name not in datas.keys() or (datas[name] != password and get_hashval(password) != hashs[datas[name]]):
        print("Failed!")
    elif datas[name] == password:
        print("Success!")
    else:
        print("Attention!")


# if __name__ == '__main__':
#     # test_get_hashval()
#     # pass
n = int(input())
for i in range(n):
    s = input().split()
    if s[0] == 'R':
        register(s[1], s[2])
    else:
        login(s[1], s[2])
