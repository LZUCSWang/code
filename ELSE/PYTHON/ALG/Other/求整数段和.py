s, e = map(int, input().split())
sum = 0
t = 1
for i in range(s, e+1):
    sum += i
    print("%5d" % (i), end='')
    if t % 5 == 0 and i != e:
        print()
    t += 1
if (e-s)+1 % 5 != 0:
    print()
print("Sum = %d" % sum)
