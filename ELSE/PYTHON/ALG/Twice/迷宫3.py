data="""
UDDLUULRUL
UURLLLRRRU
RRUURLDLRD
RUDDDDUUUU
URUDLLRRUU
DURLRLDLRL
ULLURLLRDU
RDLULLRDDD
UUDDUDUDLL
ULRDLUURRR""".split()
n,m=len(data),len(data[0])
cnt=0
seen=[[0]*m for _ in range(n)]
def dfs(i,j):
    global cnt
    if i<0 or j<0 or i>=n or j>=m:
        cnt+=1
        return
    if seen[i][j]==1:
        return
    seen[i][j]=1
    if data[i][j]=="U" :
        dfs(i-1,j)
    elif data[i][j]=="D":
        dfs(i+1,j)
    elif data[i][j]=='R':
        dfs(i,j+1)
    else:
        dfs(i,j-1)
    seen[i][j]=0
    
for i in range(n):
    for j in range(m):
        dfs(i,j)
print(cnt)