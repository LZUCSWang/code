import sys
start = 123456789
end = 876543219
seen=[0]*1000000000
queue=[(start,0)]
seen[start]=1
flags=[-2,-1,1,2]
while len(queue)>0:
    t=queue.pop(0)
    item,ti=t[0],t[1]
    ind=str(item).index('9')
    for d in flags:
        citem=list(str(item))
        citem[ind],citem[(ind+d)%9]=citem[(ind+d)%9],citem[ind]
        nowint=int(''.join(citem))
        if nowint==int(end):
            print(ti+1)
            sys.exit()
        if seen[nowint]==0:
            seen[nowint]=1
            queue.append((nowint,ti+1))
