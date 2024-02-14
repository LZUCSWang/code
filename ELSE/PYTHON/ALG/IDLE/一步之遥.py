#一步之遥
seen=[0]*1000000
from collections import deque
queue=deque([(0,0)])
while len(queue)>0:
        item=queue.popleft()
        nowplace,t=item[0],item[1]
        nx=nowplace+97
        if seen[nx]==0:
            if nx==1:
                print(t+1)
                break
            seen[nx]=1
            queue.append((nx,t+1))
        nx=nowplace-127
        if seen[nx]==0:
            if nx==1:
                print(t+1)
                break
            seen[nx]=1
            queue.append((nx,t+1))

    
