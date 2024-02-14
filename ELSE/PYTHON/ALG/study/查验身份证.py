n = int(input())
data = {'0': '1', '1': '0', '2': 'X', '3': '9', '4': '8',
        '5': '7', '6': '6', '7': '5', '8': '4', '9': '3', '10': '2'}
quan = [7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2]
flag = 0
for i in range(n):
    row = input()
    s = 0
    if row[:17].isdigit():
        for i in range(17):
            s += int(row[i])*quan[i]
        if data[str(s % 11)] != row[-1]:
            flag = 1
            print(row)
    else:
        print(row)
if flag == 0:
    print("All passed", end='')
