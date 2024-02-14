class Solution:
    def countRoutes(self, locations, start: int, finish: int, fuel: int) -> int:
        dp=[[-1]*(fuel+1) for _ in range(len(locations))]
        def dfs(start,finish,fuel):
            if dp[start][fuel] != -1:
                return dp[start][fuel]
            if not fuel and start!=finish:
                dp[start][fuel]=0
                return 0
            if fuel:
                flag=True
                for i in range(len(locations)):
                    need=abs(locations[i]-locations[start])
                    if need<=fuel:
                        flag=False
                        break
                if flag:
                    dp[start][fuel]=1 if start==finish else 0
                    return dp[start][fuel]
            sum=1 if start==finish else 0
            for i in range(len(locations)):
                if i!=start:
                    need=abs(locations[i]-locations[start])
                    if need<=fuel:
                        sum+=(dfs(i,finish,fuel-need))%(10**9 + 7)
            dp[start][fuel]=sum
            return sum
        return (dfs(start,finish,fuel))%(10**9 + 7)    
print(Solution.countRoutes(0,[1,2,3],0,2,40))