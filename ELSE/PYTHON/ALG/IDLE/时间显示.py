#时间显示
s=input()
ints=int(s[:-3])
ints%=(24*3600)
h=ints//3600
m=ints//60%60
sec=ints%60
print("%02d:%02d:%02d"%(h,m,sec))

