class node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next


stactlink = [0]*(10**5+1)
splace, startnum = map(int, input().split())
stactlink[splace] = node(startnum)
chong=set()
for i in range(startnum):
    place, num, next = map(int, input().split())
    if abs(num) not in chong:
        chong.add(abs(num))
    else:
        num=float('inf')    
    stactlink[place] = node(num, next)
cnt=[]
while splace!=-1:
    if stactlink[splace].data!=float('inf'):
        print(splace,stactlink[splace].data,stactlink[splace].next)
    else:
        cnt.append(splace)
    splace = stactlink[splace].next
for i in range(len(cnt)):
    print(cnt[i],stactlink[cnt[i]].data,stactlink[cnt[i]].next)
# print(stactlink)
