linjie = [[1, 1, 1, 0, 0, 0, 0],
          [1, 1, 0, 1, 1, 0, 0],
          [1, 0, 1, 1, 0, 1, 0],
          [0, 1, 1, 1, 1, 1, 0],
          [0, 1, 0, 1, 1, 0, 1],
          [0, 0, 0, 1, 0, 1, 1],
          [0, 0, 0, 0, 1, 1, 1], ]


def dfs(j):
    global i
    for k in range(1, 8):
        if i & (1 << (k-1)) and seen[k] == 0 and linjie[j-1][k-1] == 1:
            seen[k] = 1
            dfs(k)


data = 'abcdefg'
cnt = (1 << 7)
for i in range(1, 1 << 7):
    seen = [0]*8
    for j in range(1, 8):
        if i & (1 << (j-1)):
            seen[j] = 1
            dfs(j)
            if sum(seen) != str(bin(i)).count('1'):
                cnt -= 1
            else:
                for z in range(1,8):
                    s=bin(i)[2:]
                    if z<=len(s) and s[-z]=='1':
                        print(data[z-1],end='')
                print()
            break
print(cnt)
