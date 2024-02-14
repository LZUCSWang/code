cnt=0
for i in range(1,41):
  for j in str(i):
    if j in "2019":
      cnt+=i**2
      break
print(cnt)