# -*- coding: utf-8 -*-
# BubbleSort.py
#冒泡排序
list = [8, 1, 2, 66, 5, 123]
def BubbleSort():
    for i in range(len(list)):
        for j in range(i):
            if list[j] > list[j+1]:
                list[j],list[j+1] = list[j+1],list[j]
    return list

print("冒泡排序")
list = BubbleSort()
print(list)
