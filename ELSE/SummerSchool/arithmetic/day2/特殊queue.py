from collections import deque
q1 = deque([])
q2 = deque([])
m, n = map(int, input().split())
for i in range(m):
    datas = input()
    if datas == 'DeQueue':
        if len(q1)==0:
            print("Empty Queue")
        else:
            print(q1.popleft())
            if len(q1)< len(q2):
                q1.append(q2.popleft())
    elif datas == 'DeleteMid':
        if len(q1)==0:
            print("Empty Queue")
        else:
            t=q1.pop()
            print(t)
            while len(q1)<len(q2):
                q1.append(q2.popleft())
    else:
        if len(q1)+len(q2)==n:
            print("Full Queue")
            continue
        q2.append(int(datas[8:]))
        while len(q1)<len(q2):
            q1.append(q2.popleft())
while len(q1)>0:
    print(q1.popleft(),end='')
    if len(q2)!=0 or len(q2)==0 and len(q1)!=0:
        print(' ',end='')
while len(q2)>0:
    print(q2.popleft(),end='')
    if len(q2)!=0:
        print(' ',end='')