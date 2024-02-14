s1=input()
s3=' '.join(s1.split())
s2=''.join(s1.split())
if s2.isdigit()==1 or s2.isalpha()==1:
    print(s1.title())
else:
    k=0
    while k<len(s3):
        j=k+1
        if j<len(s3):
            if s3[k].isdigit()==1 and s3[j].isalpha()==1 or s3[k].isalpha()==1 and s3[j].isdigit()==1:
                s3=s3[:j]+'_'+s3[j:]
        k+=1
    l1=s3.split()
    l2=[]
    for i in l1:
        if i.isalnum():
            i=i.title()
        else:
            i=i[0].title()+i[1:]
        l2.append(i)
    print(' '.join(l2))
