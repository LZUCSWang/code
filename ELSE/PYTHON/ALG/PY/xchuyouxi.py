# from re import T


from calendar import c
from re import T
import sys
s = input()
if len(s)<=2:
    print(s)
    sys.exit()
# flag=[]
f = True
while f:
    f = False
    t = ''
    flag = [True]*(len(s))
    if (len(s) >= 3) and not (s[1] == s[2] and s[0] != s[1]):
        t += s[0]
    for i in range(1, len(s)-1):
        if s[i] == s[i+1] and s[i] != s[i-1]:
            # flag[i],flag[i-1]=False,False
            f = True
            continue
        if s[i] == s[i-1] and s[i] != s[i+1]:
            # flag[i],flag[i+1]=False,False
            f = True
            continue
        if i>=1 and(s[i]!=s[i+1] and s[i+1]==s[i+2]):
            f=True
            continue
        if i<len(s)-1 and s[i-1]==s[i-2] and s[i-1]!=s[i]:
            f=True
            continue
        # if i >= 2 and i < len(s)-2 and (s[i-1] == s[i-2] and s[i-1] != s[i] or s[i+1] == s[i+2] and s[i+1] != s[i]):
        #     f = True
        #     continue
        t += s[i]
    if len(s) >= 3 and not (s[-1] != s[-2] and s[-2] == s[-3]):
            t += s[-1]
    if t!='':
        s=t
print(s) if s!='' else print("EMPTY")
