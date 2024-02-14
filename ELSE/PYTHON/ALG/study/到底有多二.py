row = input()
lenth = len(row)
fu, ou = 1, 1
if row[0] == '-':
    fu = 1.5
    lenth -= 1
    irow = int(row[1::])
else:
    irow = int(row)
if irow % 2 == 0:
    ou += 1
cn = row.count('2')                 
print("{}%".format(round(fu*cn*ou*100/lenth, 2)))
