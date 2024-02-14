t=['jia','yi','bing','ding','wu','ji','geng','xin','ren','gui']
d=['zi','chou','yin','mao','chen','si','wu','wei','shen','you','xu','hai']
y=int(input())
dt=2020-y
t1=6
d1=0
print(t[(t1+dt)%10]+d[(d1+dt)%12])