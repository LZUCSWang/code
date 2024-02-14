s=input()
def isvalid(string):
    cnt=0
    for i in string:
        if i=='(':
            cnt+=1
        elif i==')':
            cnt-=1
        if cnt<0:
            return False
    return cnt==0
level=set()
level.add(s)
while True:
    v=list(filter(isvalid,level))
    if v:
        print(len(v)%10000007)
        break
    nextlevel=set()
    for item in level:
        for i in range(len(item)):
            nextlevel.add(item[:i]+'('+item[i:])
            nextlevel.add(item[:i]+')'+item[i:])
    level=nextlevel

         
