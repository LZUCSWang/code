def minPathSum(grid) -> int:
        if not grid or not grid[0]:
            return 0
        m,n=len(grid),len(grid[0])
        print(n)
        f=[[0]*n]*m
        print(f)
        sum=0
        f[0][0]=grid[0][0]
        for i in range(1,n):
            f[0][i]=f[0][i-1]+grid[0][i]
        for j in range(1,m):
            f[j][0]=f[j-1][0]+grid[j][0]
        for i in range(1,m):
            for j in range(1,n):
                f[i][j]=min(f[i-1][j],f[i][j-1])+grid[i][j]
        return f[m-1][n-1]
print(minPathSum([[7,4,8,7,9,3,7,5,0],[1,8,2,2,7,1,4,5,7],[4,6,4,7,7,4,8,2,1],[1,9,6,9,8,2,9,7,2],[5,5,7,5,8,7,9,1,4],[0,7,9,9,1,5,3,9,4]]))
dp = [[0] * 3 for _ in range(4)]
print(dp)