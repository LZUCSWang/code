pos=0
def f(s1):
    tem,max=0,0
    global pos
    lenth=len(s1)
    while pos<lenth:
        if s1[pos]=='(':
            tem+=f(s1)
        elif s1[pos]=='|':
            max=max(tem,max)
            tem=0
        elif s1[pos]=='x':
            tem+=1
        elif s1[pos]==')':
            max=max(max,tem)
            
        pos+=1

