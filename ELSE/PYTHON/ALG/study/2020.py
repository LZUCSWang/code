data="""
220000
000000
002202
000000
000022
002020
""".split()
m,n=len(data),len(data[0])
cnt=0
for i in range(m-3):
    for j in range(n-3):
        if data[i][j]=='2' and data[i][j+1]=='0' and data[i][j+2]=='2' and data[i][j+3]=='0':
            cnt+=1
        if data[i][j]=='2' and data[i+1][j]=='0' and data[i+2][j]=='2' and data[i+3][j]=='0':
            cnt+=1
        if data[i][j]=='2' and data[i+1][j+1]=='0' and data[i+2][j+2]=='2' and data[i+3][j+3]=='0':
            cnt+=1
for i in range(m-3,m):
    for j in range(n-3):
        if data[i][j]=='2' and data[i][j+1]=='0' and data[i][j+2]=='2' and data[i][j+3]=='0':
            cnt+=1
for j in range(n-3,n):
    for i in range(m-3):
        if data[i][j]=='2' and data[i+1][j]=='0' and data[i+2][j]=='2' and data[i+3][j]=='0':
            cnt+=1
print(cnt)