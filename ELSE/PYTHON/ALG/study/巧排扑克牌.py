data=[i for i in range(1, 14)]
end=list(input().split(','))
nextstep=[]
while len(nextstep)!=13:
    data.insert(0,data[-1])
    data.pop(-1)
    nextstep.append(data[-1])
    data.pop(-1)
cnt=[0]*13
for i in range(13):
    cnt[nextstep[i]-1]=end[i]
cnt=','.join(cnt[::-1])
print(cnt)