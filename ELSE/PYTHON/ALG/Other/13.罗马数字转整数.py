#
# @lc app=leetcode.cn id=13 lang=python3
#
# [13] 罗马数字转整数
#

# @lc code=start
class Solution:
    d = {
        'I': 1,
        'V': 5,
        'X': 10,
        'L': 50,
        'C': 100,
        'D': 500,
        'M': 1000,
    }

    def romanToInt(self, s: str) -> int:
        cnt = 0
        for i, ch in enumerate(s):
            value = Solution.d[ch]
            if i < len(s)-1 and value < Solution.d[s[i+1]]:
                cnt -= value
            else:
                cnt += value
        return cnt
# @lc code=end
