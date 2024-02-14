#为了灵活使用,我写一个函数，并把分解出来的质数存到列表里并输出
#怎么加工利用看自己需要
 
def f(x):
    i=2
    l=[]
    while i<=x:
        if x%i==0:
            l.append(i)
            x//=i
        else:
            i+=1
    return l
print(f(9))