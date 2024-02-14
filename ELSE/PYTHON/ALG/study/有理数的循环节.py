datas,b=map(int,input().split(','))
r=str(datas/b).split('.')
d1,d2=r[0],r[1]
i=1
while True:
    if d2[:i]==d2[i:2*i]:
        print(d1+'.'+'['+d2[:i]+']')
        break
    i+=1
