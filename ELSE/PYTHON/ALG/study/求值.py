def countyue(cnt):
    count = 0
    for i in range(1, cnt+1):
        if cnt % i == 0:
            count += 1
    return count


cnt = 1
for t in range(1, 101):
    while countyue(cnt) != t:
        cnt += 1
    cnt+=1
print(cnt-1)
