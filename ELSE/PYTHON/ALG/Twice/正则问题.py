from turtle import right


s=input()
index=0
def slove(s):
    global index
    right,left=0,0
    while index<len(s):
        if s[index]=='x':
            right+=1
        elif s[index]=='|':
            left=right
            right=0
        elif s[index]=='(':
            index+=1
            right+=slove(s)
        elif s[index]==')':
            return max(right,left) 
        index+=1
    return max(right,left)
print(slove(s))