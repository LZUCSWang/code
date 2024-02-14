data=[1]
n=int(input())
for i in range(1,n+1):
  if i%2==0:
    data.append(data[-1]+1)
  else:
    data.append(data[-1]*2)
print(data[-1])