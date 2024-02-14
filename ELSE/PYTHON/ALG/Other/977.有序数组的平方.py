#
# @lc app=leetcode.cn id=977 lang=python3
#
# [977] 有序数组的平方
#

# @lc code=start
class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        cnt=[]
        for i in range (len(nums)):
            cnt.append(nums[i]*nums[i])
        return cnt.sort()
# @lc code=end

