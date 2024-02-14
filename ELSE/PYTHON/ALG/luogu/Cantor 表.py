i,j=1,1
n=int(input())-1
flag=1#1,0分别为右上和左下
while n>0:
    n-=1
    if flag==1:
        j+=1
        i-=1
        if i==0:
            i=1
            flag=0
    elif flag==0:
        i+=1
        j-=1
        if j==0:
            j=1
            flag=1
print(i,j)
        
        