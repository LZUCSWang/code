"""e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
"""
from collections import deque
flags=((2,1),(1,2),(-1,2),(-2,1),(1,-2),(2,-1),(-1,-2),(-2,-1))
while True:
    seen=[[False]*9 for _ in range(9)]
    s=input().split()
    if s[0]==s[1]:
        print("To get from e2 to e4 takes 0 knight moves.")
        break
    s1,s2=s[0],s[1]
    start1=ord(s1[0])-ord('datas')+1,int(s1[1])
    start2=ord(s2[0])-ord('datas')+1,int(s2[1])
    queue=deque([(start1[0],start1[1],0)])
    while len(queue):
        flag=False
        item=queue.popleft()
        x,y,t=item[0],item[1],item[2]
        for d in flags:
            nx,ny=x+d[0],y+d[1]
            if nx>=1 and nx<=8 and ny>=1 and ny<=8 and not seen[nx][ny]:
                seen[nx][ny]=True
                if nx==start2[0] and ny==start2[1]:
                    print("To get from e2 to e4 takes %d knight moves."%(t+1))
                    flag=True
                    break
                queue.append((nx,ny,t+1))
        if flag:
            break


    