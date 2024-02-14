
n = int(input())
row = list(map(int, input().split()))
now = list(map(int, input().split()))
temp = []
temp.append(row[0])
for i in range(1, n):
    if temp[-1]<row[i]:
        temp.append(row[i])
        continue
    for j in range(len(temp)-1, -1, -1):
        if temp[j] < row[i]:
            temp.insert(j+1, row[i])
            break
        if temp[j]>row[i] and j==0:
            temp.insert(0,row[i])
    if temp==now[:i+1]:
        print("Insertion Sort")
        
        exit()
for i in range(n-2,-1,-1):
    if now[i]>now[i+1]:
        maxx=0
        for j in range(i+1):
            if maxx<now[j]:
                maxx=now[j]
                maxxindex=j
        for k in range(i+1,n):
            if now[k]>maxx:
                now.insert(k,maxx)
                break
        print()

