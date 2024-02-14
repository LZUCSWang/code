n,m,k,t=list(map(int,input().split()))
time=list(map(int,input().split()))
time.insert(0,0)
have=list(map(int,input().split()))
method=[]
for i in range(k):
  method.append(list(map(int,input().split())))
def dfs(seed)->int:
  if seed in have:
    return 0
  min_time=999999
  for i in method:
    if i[2]==seed:
      temp=max(time[i[0]],time[i[1]])
      mintimetemp=max(dfs(i[0]),dfs(i[1]))+temp
      if mintimetemp<min_time:
        min_time=mintimetemp
  return min_time
print(dfs(t))