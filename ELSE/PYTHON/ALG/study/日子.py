import os
import sys

# 请在此输入您的代码
monthday = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]


def judgeababa(inputstr) -> bool:
    if inputstr[0] == inputstr[2] and inputstr[2] == inputstr[5] and inputstr[5] == inputstr[7] and inputstr[1] == inputstr[3] and inputstr[3] == inputstr[4] and inputstr[4] == inputstr[6]:
        return True
    else:
        return False


def judgehuiwen(inputstr) -> bool:
    if inputstr[0] == inputstr[7] and inputstr[1] == inputstr[6] and inputstr[2] == inputstr[5] and inputstr[3] == inputstr[4]:
        return True
    else:
        return False


inputstr = input()
intyear = int(inputstr[0:4])
intmonth = int(inputstr[4:6])
intday = int(inputstr[6:8])
cnthuiwen = ""
flag = 0
intday += 1
if intyear % 4 == 0 and intmonth == 2 and intday == 30:
    intday = 1
    intmonth = 3
elif intday > monthday[intmonth-1]:
    intday = 1
    intmonth += 1
    if intmonth > 12:
        intyear += 1
        intmonth = 1
inputstr = "{:4d}{:02d}{:02d}".format(intyear, intmonth, intday)
while judgeababa(inputstr) == False:
    intday += 1
    if intyear % 4 == 0 and intmonth == 2 and intday == 30:
        intday = 1
        intmonth = 3
    elif intday > monthday[intmonth-1]:
        intday = 1
        intmonth += 1
        if intmonth > 12:
            intyear += 1
            intmonth = 1
    inputstr = "{:4d}{:02d}{:02d}".format(intyear, intmonth, intday)
    if flag == 0:
        if judgehuiwen(inputstr) == True:
            cnthuiwen = inputstr
            flag = 1
print(cnthuiwen)
print(inputstr)
