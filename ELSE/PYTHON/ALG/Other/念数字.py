import sys
row = input()
i = 0
if row == '0':
    print("ling")
    sys.exit()
if row[0] == '-':
    print('fu ', end='')
    i = 1
data = {'0': 'ling', '1': 'yi', '2': 'er', '3': 'san', '4': 'si',
        '5': 'wu', '6': 'liu', '7': 'qi', '8': 'ba', '9': 'jiu'}
while i < len(row):
    print(data[row[i]], end='')
    if i != len(row)-1:
        print(' ', end='')
    i += 1
