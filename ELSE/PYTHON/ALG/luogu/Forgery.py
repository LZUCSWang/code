n,m=map(int,input().split())
target=[list(input()) for _ in range(n)]
# print(target)
start=[['.']*m for _ in range(n)]
# print(start)
# flag=1
flags=[(0,1),(1,0),(0,-1),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]
for i in range(1,n-1):
    for j in range(1,m-1):
        flag=1
        for d in flags:
            nx,ny=i+d[0],j+d[1]
            if target[nx][ny]!='#':
                flag=0
                break
        if flag==1:
            for d in flags:
                nx,ny=i+d[0],j+d[1]
                start[nx][ny]='#'
                # flag=1
# print(start)
# print(target)
print("YES") if start==target else print("NO")
