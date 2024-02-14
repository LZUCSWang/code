p,n=map(int,input())
h=Node(next=p)
for i in range(n):
    p1,num1,n1=map(int,input().split())
    n=Node(my=p1,data=num1,next=n1)