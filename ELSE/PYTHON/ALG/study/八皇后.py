cnt,hang,zuoxia,youxia=[0]*100,[0]*100,[0]*100,[0]*100
cnt=0
n=int(input())
def dfs(i):
    global cnt
    if i>n:
        cnt+=1
        if cnt<=3:
            for i in range(1,n+1):
                print(cnt[i],end='')
            print()
        return
    for j in range(1,n+1):
        if hang[j]==0 and zuoxia[n-i+j]==0 and youxia[i+j]==0:
            hang[j],zuoxia[n-i+j],youxia[i+j]=1,1,1
            cnt[i]=j
            dfs(i+1)
            hang[j],zuoxia[n-i+j],youxia[i+j]=0,0,0
dfs(1)
print(cnt)