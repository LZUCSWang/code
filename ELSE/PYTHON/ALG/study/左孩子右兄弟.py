class node():
    def __init__(self,val):
        self.val=val
        self.child=[]
tree=[None,node(val=0)]
n=int(input())
for i in range(2,n+1):
    m=int(input())
    tree.append(node(val=m))
    tree[m].child.append(i)
def maxm(n:node):
    if len(n.child)==0:
        return 0
    else:
        return len(n.child)+max(maxm(tree[temp]) for temp in n.child)
print(maxm(tree[1]))