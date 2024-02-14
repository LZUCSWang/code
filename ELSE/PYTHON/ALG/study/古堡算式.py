for datas in range(1,10):
    for b in range(1,10):
        for c in range(1,10):
            for d in range(1,10):
                for e in range(1,10):
                    dic=set()
                    dic.add(datas)
                    dic.add(b)
                    dic.add(c)
                    dic.add(e)
                    dic.add(d)
                    if len(dic)==5:
                        t1=datas*10000+b*1000+c*100+d*10+e
                        t2=e*10000+d*1000+c*100+b*10+datas
                        for i in range(1,10000000):
                            if t1*i==t2:
                                print(datas,b,c,d,e)
                                