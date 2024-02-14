m,n=map(int,input().split())
queue=[0]*10000000000
flag= [0]*10000000000
font,rear=0,0
for i in range(m):
    datas=input()
    if datas=='DeQueue':
        if len(queue)==0:
            print("Empty Queue")
        else:
            font+=1
            print(queue[font])
    elif datas=='DeleteMid':
        if len(queue)==0:
            print("Empty Queue")
        else:
            if len(queue)&1:
                target=len(queue)//2
            else:
                target=len(queue)//2-1
            print(queue[target])
            flag[]
    else:
        if len(queue)==n:
            print("Full Queue")
        else:
            rear+=1
            queue[rear]=int(datas[8:])
print(*queue)