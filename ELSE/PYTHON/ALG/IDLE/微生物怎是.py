class Solution:
    #我的思路是设置x每6分钟分裂一次，y每4分钟分裂一次。一个新出生x，
    #一分钟吃掉一个Y,从此以后，每两分钟吃掉一个Y
    #问2*time后y剩余的总数
    def microbialProliferation(self,datas,b,time):
        new_a=datas
        for i in range(1,2*time+1):
            if i%2==1:
                b-=datas
            if i!=1 and i%4==0:
                b*=2
            if i!=1 and i%6==0:
                new_a=datas
                datas*=2
        return b if b>0 else 0


if __name__=='__main__':
    solution=Solution
    datas=10
    b=90
    time=60
    res=solution.microbialProliferation(solution,datas,b,time)
    print(res)
