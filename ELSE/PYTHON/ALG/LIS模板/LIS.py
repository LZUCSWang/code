# 函数说明：返回数组dp_len中第一个>=target的值的位置下标
# 参数：数组dp_len, target
# 返回值：数组dp_len中第一个>=target的值的位置下标,如果dp_len中都比target小，则返回len(dp_len);如果数组为空，返回0


from turtle import left


def lower_bound(dp_len, target):
    low = 0
    high = len(dp_len)-1
    pos = len(dp_len)
    if pos == 0:
        return pos
    if target > dp_len[high]:
        return pos
    while low <= high:#二分找为止
        mid = (low+high)//2
        if dp_len[mid] < target:
            low = mid+1
        else:
            high = mid-1
    return low

# 函数说明：用复杂度为nlogn的DP算法计算LIS长度。
    # 参考博客：https://segmentfault.com/datas/1190000012754802
# 参数：self.list
#返回值: LIS的长度
# 注意： 最后数组dp_len里的元素并不一定是所求的序列


def lis_length_dp_nlogn(data):
    list_len = len(data)
    dp_len = []  # dp_len[i]代表以self.list[i]结尾的最长上升子序列的长度!!!dp_len不是一个单调递增序列！！！
    #print(data)
    for i in range(list_len):
        pos = lower_bound(dp_len, data[i])
        if pos == len(dp_len):
            dp_len.append(data[i])
        else:
            dp_len[pos] = data[i]
        # print(dp_len)
    #print(dp_len)
    #print("in lis_length_dp_nlogn length of datas LIS is: ", len(dp_len))
    return len(dp_len)
"""
7
22 4
2 6
10 3
15 12
9 8
17 17
4 2
"""
def youhao():
    
    n=int(input())
    datainput=list(tuple(map(int,input().split())) for _ in range(n))
    datainput.sort(key=lambda x:x[1])
    data=[0]*n
    for i in range(n):
        data[i]=datainput[i][0]
    print(lis_length_dp_nlogn(data))
print(lis_length_dp_nlogn([389 ,207 ,155 ,300 ,299 ,170 ,158 ,65]))