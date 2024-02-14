ox=2019
jishu="24680"
for i in range(3,1000):
    flag=0
    x=ox*i
    for j in str(x):
        if j in jishu:
            flag=0
            break
        flag=1
    if flag==1:
        print(x)
        break
# 请在此输入您的代码