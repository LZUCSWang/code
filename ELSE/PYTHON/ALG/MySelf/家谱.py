last = {}
s = f = input()
last[s[1:]] = s[1:]


def find(s):
    if last[s] != s:
        last[s] = find(last[s])
    return last[s]


while True:
    f = s
    if f[0] == '?':
        break
    if f[1:] not in last.keys():
        last[f[1:]] = f[1:]
    while True:
        s = input()
        if s[0] != '+':
            break
        last[s[1:]] = f[1:]
print(s[1:]+' '+find(s[1:]))
while True:
    s = input()
    if s == '$':
        break
    print(s[1:]+' '+find(s[1:]))
