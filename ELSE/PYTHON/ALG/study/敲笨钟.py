n = int(input())
for i in range(n):
    row = input()
    row1 = row.split(',')
    r1, r2 = row1[0].split(), row1[1].split()
    if len(r1[-1]) >= 3 and len(r2[-1]) >= 4 and r1[-1][-3:] == 'ong' and r2[-1][-4:-1] == 'ong':
        r2[-1]='zhong.'
        r2[-2]='ben'
        r2[-3]='qiao'
        print(' '.join(r1)+', '+' '.join(r2))
    else:
        print("Skipped")
