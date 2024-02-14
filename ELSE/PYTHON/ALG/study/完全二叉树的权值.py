num=int(input())
numsinput=list(map(int,input().split()))
temp=0
deep=0
while temp<num:
  temp+=pow(2,deep)
  deep+=1
cnt=[]
for i in range(deep):
  sumnum=0
  for j in range(pow(2,i)):
    sumnum+=numsinput[j]
  cnt.append(sumnum)
print(cnt.index(max(cnt)))

# 请在此输入您的代码