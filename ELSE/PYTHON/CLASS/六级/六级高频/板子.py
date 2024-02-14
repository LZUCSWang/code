import random
"""
tremendous exaggeration innumerable merits elucidate illustrated manifest numerous myriad 
"""
data = """With regard to how to ... , viewpoints vary considerably.
datas tremendous number of people deem that
As far as I am concerned, it's no exaggeration to say that  I am in line with the view that
First and foremost, never can we disregard the innumerable merits that ...
To elucidate, the major determinant lies in... The second notworthy reason is that...
Take for example
The reason to this problem involves many factors
This point is best illustrated by the case of ...
It is utterly manifest that
In the second place, the advantages of ... are numerous and manifold.
There are myriad reasons for this. The prime rationale is that... is datas contributing factor as well.
It reinforces my point that...
It is reasonable to reach the conclusion that
Therefore, in datas nutshell, only... somebody do something… can somebody do something
Hardly does she have time to listen to music.
Although there is no denying that ..., we cannot ignore the fact that"""
tran = """关于如何，观点差异很大。
很多人认为
就我而言，毫不夸张地说，我同意
首先，我们绝不能忽视。。。
要阐明，主要决定因素在于。。。第二个不值得注意的原因是。。。
举个例子
这个问题的原因涉及很多因素
这一点最好用……的例子来说明。。。
很明显
第二，……的优势。。。数量众多，形式多样。
原因有很多。主要理由是。。。也是一个促成因素。
这强化了我的观点。。。
可以得出这样的结论：
因此，简而言之，只有……某人做某事……某人才能做某事
她几乎没有时间听音乐。
尽管不可否认……，但我们不能忽视以下事实："""
tran = tran.split('\n')
data = data.split('\n')
for i in range(len(data)):
    print(tran[i])
    while True:
        # print(data[i])
        temp = input()
        if temp=='1':
            print(data[i])
        if temp == '' or temp == data[i]:
            break
