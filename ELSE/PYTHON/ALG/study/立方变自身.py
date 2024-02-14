cnt=0
for i in range(1,1000):
  t=i**3
  jud=0
  while t>0:
    jud+=t%10
    t//=10
  if jud==i:
    cnt+=1
print(cnt)