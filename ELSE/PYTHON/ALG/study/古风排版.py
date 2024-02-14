n = int(input())
s = input()
width = len(s)//n if len(s) % n == 0 else len(s)//n+1
data = [[' ']*width for _ in range(n)]
i, j ,t= 0, width-1,0
while t < len(s):
    if i == n:
        i,j=0,j-1
    data[i][j] = s[t]
    i,t=i+1,t+1
for i in data:
    print(''.join(i))
