import sys
t = input()
h, m = int(t[:2]), int(t[3:])
if h >= 0 and h < 12 or h == 12 and m == 0:
    print("Only %s.  Too early to Dang." % t)
    sys.exit()
dang = h-12
if m != 0:
    dang += 1
print("Dang"*dang, end='')
