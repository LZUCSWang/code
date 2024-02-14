import random
f = open('./data.txt', 'r', encoding='utf-8')
data = f.read().split('\n')
for str in random.sample(data, len(data)):
    if str == '':
        continue
    print(str[3:])
