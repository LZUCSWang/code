def uniquePathsWithObstacles(obstacleGrid) -> int:
        m,n=len(obstacleGrid),len(obstacleGrid[0])
        print(m,n)
        if m==1 or n==1:
            if m==1 :
                for i in range(n):
                    if obstacleGrid[0][i]==1:
                        return 0
                return 1
            else:
                for i in range(m):
                    if obstacleGrid[i][0]==1:
                        return 0
                return 1
        f=[[1]*n]+[[1]+[0]*(n-1) for _ in range(m-1)]
        for i in range(n):
            if obstacleGrid[0][i]==1:
                for j in range(i,n):
                    f[0][j]=0
                break
        for i in range(m):
            if obstacleGrid[i][0]==1:
                for j in range(i,m):
                    f[j][0]=0
                break
        print(f)
        for i in range(1,m):
            for j in range(1,n):
                if obstacleGrid[i][j]==1:
                    f[i][j]=0
                else:
                    f[i][j]=f[i-1][j]+f[i][j-1]
        print(f)
        return f[m-1][n-1]
print(uniquePathsWithObstacles([[0,1],[1,0]]))