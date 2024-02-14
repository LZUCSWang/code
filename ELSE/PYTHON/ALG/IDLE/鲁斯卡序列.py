#鲁卡斯队列
datas,b,c=1,3,0
for i in range(3,100):
    c=datas+b
    cntstr=str(b/c)
    if round(b/c,6)==0.618034:
        print("%d/%d"%(b,c))
        break
    datas,b,c=b,c,0
