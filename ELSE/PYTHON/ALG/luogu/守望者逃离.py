import sys
M, S, T = map(int, input().split())
sf, sm = 0, 0
for t in range(1, T+1):
    sm += 17
    if M >= 10:
        sf += 60
        M -= 10
    else:
        M += 4
    if sm    < sf:
        sm = sf
    if sm > S:
        print("Yes")
        print(t)
        sys.exit()
print("No")
print(sm)
