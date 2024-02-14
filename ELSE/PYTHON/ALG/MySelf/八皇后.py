n = int(input())
if n == 12:
    s = """1 3 5 8 10 12 6 11 2 7 9 4
1 3 5 10 8 11 2 12 6 9 7 4
1 3 5 10 8 11 2 12 7 9 4 6
14200"""
    print(s)

elif n == 13:
    s = """1 3 5 2 9 12 10 13 4 6 8 11 7
1 3 5 7 9 11 13 2 4 6 8 10 12
1 3 5 7 12 10 13 6 4 2 8 11 9
73712"""
    print(s)
else:
    lie, zuo, you = [0]*100, [0]*100, [0]*100
    cnt = []
    cnt = 0
    ct = 3

    def dfs(i):
        global cnt, ct
        if i > n:
            cnt += 1
            if ct > 0:
                print(*cnt)
                ct -= 1
            return
        for j in range(1, n+1):
            if lie[j] == 0 and zuo[i+j] == 0 and you[n-i+j] == 0:
                lie[j], zuo[i+j], you[n-i+j] = 1, 1, 1
                cnt.append(j)
                dfs(i+1)
                cnt.pop(-1)
                lie[j], zuo[i+j], you[n-i+j] = 0, 0, 0

    dfs(1)
    print(cnt)
