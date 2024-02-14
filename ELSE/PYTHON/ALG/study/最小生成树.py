# 连通网:最小生成树
# 定义获取两城邦权值函数

parent = [i for i in range(0, 2022)] # 初始化祖先


def find_root(x):  # 查找集合[路径压缩]
    if x != parent[x]:
        parent[x] = find_root(parent[x])
    return parent[x]


def union(x, y):  # 合并集合
    x_root, y_root = find_root(x), find_root(y)
    if x_root != y_root:
        parent[y_root] = x_root


def get_weight(x, y):  # 获取权值
    datas = '0'*(4-len(str(x)))+str(x)
    b = '0'*(4-len(str(y)))+str(y)
    s = 0
    for i in range(4):
        if datas[i] != b[i]:
            s += int(datas[i])+int(b[i])
    return s


edge = []  # 创建边集(i,j,weight)
for i in range(1, 2022):
    for j in range(1, 2022):
        edge.append((i, j, get_weight(i, j)))
edge.sort(key=lambda x: x[2])  # 关键字排序

count = 0
j = 1

for i in edge:
    try:
        if find_root(i[0]) != find_root(i[1]) and j <= 2020:  # 不处在同一连通分量(集合)且点数未达到2021-1
            count += i[2]  # 累加
            union(i[0], i[1])  # 合并
            j += 1
    except:  # 检查报错点
        print(i[0], i[1])
        break
print(count)  # 答案是4046