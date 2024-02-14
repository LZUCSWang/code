data="""UDDLUULRUL
UURLLLRRRU
RRUURLDLRD
RUDDDDUUUU
URUDLLRRUU
DURLRLDLRL
ULLURLLRDU
RDLULLRDDD
UUDDUDUDLL
ULRDLUURRR""".split()
m,n=len(data),len(data[0])
cnt=0
def slove(x,y):
    if x>=n or x<0 or y>=n or y<0:
        return True
    if flag[x][y]==1:
        return False
    flag[x][y]=1
    if data[x][y]=='U':
        return slove(x-1,y)
    if data[x][y]=='D':
        return slove(x+1,y)
    if data[x][y]=='R':
        return slove(x,y+1)
    if data[x][y]=='L':
        return slove(x,y-1)
for i in range(m):
    for j in range(n):
        flag=[[0]*n]*m
        if slove(i,j):
            cnt+=1
print(cnt)
