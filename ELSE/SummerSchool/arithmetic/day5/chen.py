n = int(input())
hou = list(map(int, input().split()))
zhong = list(map(int, input().split()))
q = []
t = hou[-1]
gen_pos = zhong.index(t)
q.append(gen_pos)
print(t, end='')
if n!=1:
    print(" ",end='')
seen = [0]*(10000+1)
seen[t] = 1
cnt=1
while len(q) > 0 and cnt<n:
    gen_pos = q.pop(0)
    if gen_pos > 0:
        j = gen_pos-1
        while j >= 0 and seen[zhong[j]] == 0:
            j -= 1
        for i in range(n-1, -1, -1):
            if hou[i] in zhong[j+1:gen_pos] and seen[hou[i]] == 0:
                print(hou[i], end='')
                cnt+=1
                if cnt!=n:
                    print(" ",end='')
                pos = zhong.index(hou[i])
                seen[hou[i]] = 1
                q.append(pos)
                break
    if gen_pos < n-1:
        j = gen_pos+1
        while j <= n-1 and seen[zhong[j]] == 0:
            j += 1
        for i in range(n-1, -1, -1):
            if hou[i] in zhong[gen_pos+1:j] and seen[hou[i]] == 0:
                print(hou[i], end='')
                cnt+=1
                if cnt!=n:
                    print(" ",end='')
                pos = zhong.index(hou[i])
                seen[hou[i]] = 1
                q.append(pos)
                break
