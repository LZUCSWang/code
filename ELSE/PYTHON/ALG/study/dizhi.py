target=int(input())
arry="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
cnt=[]
while target>1:
  cnt.append(arry[target%26-1])
  target//=26
print(''.join(cnt[::-1]))