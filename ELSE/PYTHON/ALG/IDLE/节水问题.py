#节水问题
n,k=map(int,input().split())
data=list(map(int,input().split()))
now=[i for i in data[:k]]
from collections import deque
queue=deque(data[k:])
cnt=0
time=0
while len(queue)>0:
    minnow=min(now)
    time=minnow-time
    ind=now.index(minnow)
    item=queue.popleft()
    now[ind]+=item
print(max(now))
    
    
