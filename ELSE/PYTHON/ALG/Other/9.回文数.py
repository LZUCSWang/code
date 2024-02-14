#
# @lc app=leetcode.cn id=9 lang=python3
#
# [9] 回文数
#

# @lc code=start
class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        cnt = 0
        temp = x
        while x != 0:
            cnt = cnt*10+x % 10
            x //= 10
        if temp == cnt:
            return True
        else:
            return False
# @lc code=end
