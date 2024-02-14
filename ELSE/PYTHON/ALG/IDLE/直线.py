#直线
point=[(x,y) for x in range(0,20) for y in range(0,21)]
cnt=set()
for datas in point:
    for b in point:
        if datas!=b and datas[0]!=b[0]:
            xa,ya,xb,yb=datas[0],datas[1],b[0],b[1]
            k=(ya-yb)/(xa-xb)
            b=(yb*xa-ya*xb)/(xa-xb)
            cnt.add((k,b))
print(len(cnt)+20)

