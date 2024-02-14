import os
import sys
print(20120312)
today=20120312
posiboly=[]
for test in range(19000000,20120000):
            if test>today:
                continue
            year=test//10000
            month=test%10000//100
            day=test%100
            if day<31 and year>1900 and year <2012 and month==6 and test%2012==0 and test%3==0 and test%12==0:
                posiboly.append(test)
print(posiboly[0])
# 请在此输入您的代码