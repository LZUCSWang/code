from itertools import permutations as p
datas=['1','9','4','9']
s=set()
cnt=0

def check(x):
    for i in range(2,int(x**0.5)+1):
        if x%i==0:
            return False
    return True
for item in p(datas):
    num=int(''.join(item))
    if num not in s:
        s.add(num)
        if check(num):
            cnt+=1
print(cnt)