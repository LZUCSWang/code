#
# @lc app=leetcode.cn id=14 lang=python3
#
# [14] 最长公共前缀
#

# @lc code=start
class Solution:
    def get(self, strs1, strs2) -> str:
        length = min(len(strs1), len(strs2))
        n = 0
        while n < length and strs1[n] == strs2[n]:
            n += 1
        return strs1[:n]

    def longestCommonPrefix(self, strs: List[str]) -> str:
        if not str:
            return ""
        index, perfix = 0, strs[0]
        for i in range(1, len(strs)):
            perfix = self.get(perfix, strs[i])
            if not perfix:
                break
        return perfix
# @lc code=end
