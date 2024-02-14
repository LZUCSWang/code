n=100
import sys
for item in range(1,1000000000000000):
    s=set()
    for i in range(1,int(item**0.5)+1):
        if item%i==0:
            s.add(i)
            s.add(item//i)
    if len(s)==100:
        print(item)
        sys.exit()