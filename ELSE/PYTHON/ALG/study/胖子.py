n=int(input())
ai='duo chi yu!'
shou='duo chi rou!'
pan='shao chi rou!'
ok='wan mei!'
gao='ni li hai!'
for i in range(n):
    sex,h,w=map(int,input().split())
    if sex==1:
        if h>130:
            print(gao,end='')
        elif h<130:
            print(ai,end='')
        else:
            print(ok,end='')
        if w>27:
            print(pan)
        elif w<27:
            print(shou)
        else:
            print(ok)
    else:
        if h>129:
            print(gao,end='')
        elif h<129:
            print(ai,end='')
        else:
            print(ok,end='')
        if w>25:
            print(pan)
        elif w<25:
            print(shou)
        else:
            print(ok)