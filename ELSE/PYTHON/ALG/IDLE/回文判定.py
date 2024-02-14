#回文判定
s=input()
left,right=0,len(s)-1
while left<right:
    if s[left]!=s[right]:
        print('N')
        import sys
        sys.exit()
    left+=1
    right-=1
print('Y')
