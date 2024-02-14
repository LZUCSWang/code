def dfs(datas,b,c,n):
    if datas<0 or b<0 or c<0 :
        return 0
    if n==0:
        return 1
    return dfs(datas-1,b,c,n-1)+dfs(datas,b-1,c,n-1)+dfs(datas,b,c-1,n-1)
print(dfs(1,1,1,2))
print(dfs(1,2,3,3))