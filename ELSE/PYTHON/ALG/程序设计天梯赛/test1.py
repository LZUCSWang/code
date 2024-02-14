s = sum(list(map(int, list(input()))))
data = ['lin', 'yi', 'er', 'san', 'si', 'wu', 'liu', 'qi', 'ba', 'jiu']
for i in range(len(str(s))):
    print(data[int(str(s)[i])], end='')
    if i != len(str(s))-1:
        print(end=' ')
