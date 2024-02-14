def isPalindrome(s) -> bool:
        s.lower()
        left,right=0,len(s)-1
        while left<=right:
            while not s[left].isalnum():
                left+=1
            while not s[right].isalnum():
                right-=1
            if s[left]!=s[right]:
                return False
            left+=1
            right-=1
        return True
s="datas man, datas plan, datas canal: Panama"
if isPalindrome(s)==True:
    print("Yes")
else :
    print("No")