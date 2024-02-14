import pandas as pd
from time import time
from env import Env_tsp
from config import Config, load_pkl, pkl_parser
from search import sampling, active_search
from test import search_tour
from env import get_2city_distance
import math
import os
import torch
import copy
iniE = 100000
os.environ["CUDA_VISIBLE_DEVICES"] = "-1"  ###指定此处为-1即可
datapath = '/home/stu_wxy/content/TSP_DRL_PtrNet-master/data.csv'
# 假设你的数据已经存储在一个名为 df 的 Pandas DataFrame 中
df = pd.read_csv(datapath)

# 根据列的位置来分配x和y坐标
idx_column = 0
x_column = 1  # 假设x坐标在第一列（从0开始计数）
y_column = 2  # 假设y坐标在第二列（从0开始计数）

# 根据 x 和 y 坐标的正负值将数据分为四个象限
quadrant1 = df[(df.iloc[:, x_column] > 0) & (df.iloc[:, y_column] > 0)]
quadrant2 = df[(df.iloc[:, x_column] < 0) & (df.iloc[:, y_column] > 0)]
quadrant3 = df[(df.iloc[:, x_column] < 0) & (df.iloc[:, y_column] < 0)]
quadrant4 = df[(df.iloc[:, x_column] > 0) & (df.iloc[:, y_column] < 0)]

# print(quadrant1.dtypes)
# 打印每个象限的数据
print("第一象限数据：")
print(quadrant1)

print("\n第二象限数据：")
print(quadrant2)

print("\n第三象限数据：")
print(quadrant3)

print("\n第四象限数据：")
print(quadrant4)
# 初始化四个变量来存储每个象限的坐标信息
M1 = []
M2 = []
M3 = []
M4 = []

# print(1)
cfg = load_pkl(pkl_parser().path)
env = Env_tsp(cfg)


# search_tour(cfg, env, M2)
# print()


def routing(M, num=0, fromCity=None):
    if (len(M) == 5):
        cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test5.pkl')
    elif (len(M) == 6):
        cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test6.pkl')
    elif (len(M) == 7):
        cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test7.pkl')
    elif (len(M) == 8):
        cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test8.pkl')
    elif (len(M) == 9):
        cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test9.pkl')
    elif (len(M) == 10):
        cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test10.pkl')
    env = Env_tsp(cfg)
    return search_tour(cfg, env, M, num, fromCity)


# fly to near

def findNearPoint(quadrant):
    minDis = 999999999
    cnt = 0
    for index, row in quadrant.iterrows():
        cnt += 1
        # idx[cnt] = index
        x = row.iloc[x_column]
        y = row.iloc[y_column]
        # point = (x, y)
        get2citydis = math.sqrt(x * x + y * y)
        if get2citydis < minDis:
            minDis = get2citydis
            minRowIndex = index
            minIndex = cnt
    return minIndex - 1, minRowIndex


firstPointIndex1, firstPointRowIndex1 = findNearPoint(quadrant1)
firstPointIndex2, firstPointRowIndex2 = findNearPoint(quadrant2)
firstPointIndex3, firstPointRowIndex3 = findNearPoint(quadrant3)
firstPointIndex4, firstPointRowIndex4 = findNearPoint(quadrant4)
print()
visit = [0] * 25
visit[firstPointRowIndex1] = 1
visit[firstPointRowIndex2] = 1
visit[firstPointRowIndex3] = 1
visit[firstPointRowIndex4] = 1

# 根据 x 和 y 坐标的正负值将数据分为四个象限，并同时存储到相应的变量中
nowPoint = [0] * 5

nowPoint[1] = firstPointIndex1
nowPoint[2] = firstPointIndex2
nowPoint[3] = firstPointIndex3
nowPoint[4] = firstPointIndex4

for index, row in df.iterrows():
    # if visit[index] == 0:
    x = row.iloc[x_column]
    y = row.iloc[y_column]

    if x > 0 and y > 0:
        M1.append((x, y))
    elif x < 0 and y > 0:
        M2.append((x, y))
    elif x < 0 and y < 0:
        M3.append((x, y))
    elif x > 0 and y < 0:
        M4.append((x, y))
# else:
#     pass
# 打印每个象限的坐标信息
print("第一象限数据：")
print(M1)

print("\n第二象限数据：")
print(M2)

print("\n第三象限数据：")
print(M3)

print("\n第四象限数据：")
print(M4)

# idx映射
idx1, idx2, idx3, idx4 = {}, {}, {}, {}
allidx = [0, idx1, idx2, idx3, idx4]


def mapIndex(quadrant, idx):
    cnt = 0
    for index, row in quadrant.iterrows():
        # if visit[index] == 0:
        cnt += 1
        idx[cnt] = index


mapIndex(quadrant1, idx1)
mapIndex(quadrant2, idx2)
mapIndex(quadrant3, idx3)
mapIndex(quadrant4, idx4)

path1all, path2all, path3all, path4all = [], [], [], []

path1 = routing(M1, 1).tolist()

path1all.append(path1)
# next1city = path1[]
# print(path1)
nextPoint = [0] * 5

path2 = routing(M2, 2)

path2all.append(path2)
path3 = routing(M3, 3)
path3all.append(path2)
path4 = routing(M4, 4)
path4all.append(path2)
pathall = [0, path1, path2, path3, path4]


def printPath(num):
    for i in pathall[num]:
        if i == nowPoint[num]:
            pathFromNow = path1[i - 1:] + path1[:i - 1]
            # print(pathFromNow+1)
            for j in pathFromNow:
                print(allidx[num][j + 1], end=' ')
            nextPoint[num] = path1[(i + 1) % len(path1)]
            return pathFromNow
remainE = [0]+[iniE]*4
remainE_copy = copy.deepcopy(remainE)
def flyE():
    pass
def usedE():
    pass
def cntE(num):
    remainE_copy = copy.deepcopy(remainE)
    for i in range(1,5):
        remainE_copy[i]-=flyE()
        remainE_copy[i]-=usedE()

def centerRouting():
    allERemain=remainE_copy.sum()
    # for i in range(1,5):
    for i in range(1,25):
        if visit[i]==1:
            continue

def test():
    cfg = load_pkl('/home/stu_wxy/content/TSP_DRL_PtrNet-master/Pkl/test6.pkl')
    env = Env_tsp(cfg)

    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    # Convert the input list or array to a PyTorch tensor
    nodes = torch.tensor(M1, dtype=torch.float32, device=device)
    print(env.get_tour_distance(nodes, torch.tensor([1, 5, 4, 2, 0, 3], dtype=torch.long, device=device)))
# test()
