cnt=0
def judge(num)->bool:
  for i in str(num):
    if i=='2' or i=='4':
      return False
  return True
for i in range(1,2018):
  for j in range(i+1,2018):
    for k in range(j+1,2018):
      if i+j+k==2019 and judge(i) and judge(j) and judge(k):
        cnt+=1
print(cnt)