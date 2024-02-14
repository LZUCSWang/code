def toolow(s):
    cnt=[]
    for i in s:
        if i!='I':
            cnt.append(i.lower())
        else:
            cnt.append(i)
    return ''.join(cnt)
def tocloser(s):
    temp=s.split()
    return ' '.join(temp)
def re(s):
    
    s.replace("can you","I can")
    s.replace("could you","I could")