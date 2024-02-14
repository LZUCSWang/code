import os
import sys
s = input()
index = 0


def cnt(s):
    global index
    right, left = 0, 0
    while True:
        if index >= len(s) or s[index] == ')':
            return max(left, right)
        elif s[index] == '(':
            index += 1
            right += cnt(s)
        elif s[index] == 'x':
            right += 1
        elif s[index] == '|':
            left = max(right, left)
            right = 0
        index += 1


print(cnt(s))
# 请在此输入您的代码
