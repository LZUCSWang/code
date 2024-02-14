n=int(input())
qian,hou=[],[]
for i in range(n//2):
    t=tuple(input().split())
    qian.append(t)
for i in range(n//2):
    t=tuple(input().split()) 
    hou.append(t)
for i in range(n//2):
    if qian[i][0]=='0':
        for j in range(len(hou)-1,-1,-1):
            if hou[j][0]=='1':
                print(qian[i][1],hou[j][1])
                del hou[j]
                break
    else:
        for j in range(len(hou)-1,-1,-1):
            if hou[j][0]=='0':
                print(qian[i][1],hou[j][1])
                del hou[j]
                break