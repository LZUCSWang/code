#collcetions
from collections import deque
datas=deque([1,2,3])
datas.append(1)
datas.appendleft(3)
if len(datas)>0:
    print(datas)
    datas.pop()
    print(datas)
    print(datas.popleft(),datas)
