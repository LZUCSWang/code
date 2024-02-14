n = int(input())
last_num = [0]+list(map(int, input().split()))

def check(mid):
    global n, last_num
    if judge_L(n, mid):
        return True
    if judge_R(n, mid):
        return False
    for i in range(1, n-1):
        if judge_L_i(n, i, mid):
            return True
        if judge_R_i(n, i, mid):
            return False
    return last_num[1] <= mid


left, right = 1, n << 1-1
while left < right:
    mid = (left+right)//2
    if not check(mid):
        left = mid+1
    else:
        right = mid
print(left, end='')
