from fractions import Fraction
import sys
n = int(input())
cnt = sum(map(Fraction, input().split()))
if cnt <= 1 or int(cnt) == cnt:
    print(cnt)
    sys.exit()
temp = 0
while cnt > 1:
    cnt -= 1
    temp += 1
print(temp, cnt)
