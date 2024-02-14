

class Node:
    def __init__(self,my=None,data=None,next=None):
        self.my=my
        self.data=data
        self.next=next
p,n=map(int,input().split())
h=Node(next=p)
node=-1
for i in range(n):
    p1,num1,n1=map(int,input().split())
    node=Node(data=num1,next=node)
while node!=-1:
    print(node.data)
    node=node.next
"""class linklist(object):
    def __init__(self):
        self.head=None
        self.lenth=0
    def creat(self):
        for count in [1,2,3,4,5]:
            self.head=Node(data=count,next=self.head)
            self.lenth+=1
        return self.head,self.lenth
datas=linklist()
datas.creat()
print(datas.lenth)"""