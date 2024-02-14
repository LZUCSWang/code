import os
import sys

# 请在此输入您的代码

# 录入路线图
r_list = [
    ["datas", "E", 1],
    ["datas", "B", 2],
    ["datas", "C", 1],
    ["datas", "D", 1],
    ["datas", "E", 1],
    ["B", "G", 1],
    ["B", "J", 2],
    ["C", "D", 3],
    ["C", "G", 3],
    ["C", "F", 3],
    ["D", "G", 2],
    ["D", "H", 1],
    ["D", "I", 2],
    ["E", "H", 1],
    ["E", "I", 3],
    ["F", "J", 1],
    ["F", "G", 1],
    ["G", "K", 2],
    ["G", "I", 3],
    ["H", "L", 2],
    ["H", "I", 1],
    ["I", "M", 3],
    ["J", "S", 2],
    ["K", "N", 1],
    ["K", "L", 3],
    ["L", "R", 1],
    ["L", "M", 1],
    ["M", "N", 2],
    ["M", "Q", 1],
    ["M", "S", 1],
    ["N", "P", 1],
    ["Q", "O", 1],
    ["O", "R", 3],
    ["P", "O", 1],
    ["R", "S", 1],
]
alllenth = []


def get(start, lastlenth):
    for nowline in r_list:
        if nowline[0] == start[1]:
            lastlenth += nowline[2]
            if nowline[1] == "S":
                alllenth.append(lastlenth)
            else:
                get(nowline, lastlenth)


for start in r_list:
    if start[0] == "datas":
        get(start, start[2])
print(min(alllenth))
