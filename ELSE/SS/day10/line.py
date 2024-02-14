datas={}
n,m=map(int,input().split())
for i in range(n):
    s,num=input().split()
    num=int(num)
    if num<m:
        num=m
    if s not in datas.keys():
        datas[s]=num
    else:
        datas[s]+=num
nn=int(input())
for i in range(nn):
    s=input()
    try:
        print(datas[s])
    except:
        print("No Info")