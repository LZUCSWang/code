import copy
import os
import math
from env import get_2city_distance
import torch
from search import sampling, active_search
from config import Config, load_pkl, pkl_parser
from env import Env_tsp
from time import time
import pandas as pd
from test import search_tour

M = 1.5
g = 9.8
rou = 1.024
s = 0.2
h = 6
EF = pow(M, 1.5) * pow(g ** 3 / (2 * rou * s * h), 0.5)
iniE = 2720000
remainE = [0] + [iniE] * 4
eap = 20000


def routing(M, num=0, fromCity=None):
    cfg = load_pkl('Pkl/test' + str(len(M)) + '_10.pkl')
    env = Env_tsp(cfg)
    return search_tour(cfg, env, M, num, fromCity)


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


# os.environ["CUDA_VISIBLE_DEVICES"] = "-1"  ###指定此处为-1即可
datapath = 'data.csv'
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

# 初始化四个变量来存储每个象限的坐标信息
M1 = []
M2 = []
M3 = []
M4 = []
MM = [0, M1, M2, M3, M4]
# cfg = load_pkl(pkl_parser().path)
# env = Env_tsp(cfg)
cfg = ''
env = ''

# fly to near


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


def printPath(num, pathall):
    for i in range(len(pathall[num])):
        if pathall[num][i] == nowPoint[num]:
            pathFromNow = pathall[num][i:] + pathall[num][:i]
            # for j in pathFromNow:
            #     print(allidx[num][j + 1], end=' ')
            nextPoint[num] = pathall[num][(i + 1) % len(pathall[num])]
            return pathFromNow


def printPatht(num, pathall):
    for i in range(len(pathall[num])):
        if idxt_all[num][pathall[num][i] + 1] == nowPointRow[num]:
            pathFromNow = pathall[num][i:] + pathall[num][:i]
            # for j in pathFromNow:
            #     print(allidx[num][j + 1], end=' ')
            nextPointt[num] = pathall[num][(i + 1) % len(pathall[num])]
            return pathFromNow


def flyE(i, pathFromNowRow_all):
    d = 0
    for j in range(1, len(pathFromNowRow_all[i])):
        d += math.sqrt(
            (df.iloc[pathFromNowRow_all[i][j], x_column] - df.iloc[pathFromNowRow_all[i][j - 1], x_column]) ** 2 + (
                    df.iloc[pathFromNowRow_all[i][j], y_column] - df.iloc[
                pathFromNowRow_all[i][j - 1], y_column]) ** 2)
    d += math.sqrt(
        df.iloc[pathFromNowRow_all[i][-1], x_column] ** 2 + df.iloc[pathFromNowRow_all[i][-1], y_column] ** 2)
    return d * EF


def usedE(num, pathFromNowRow_all):
    usedEn = 0
    for i in pathFromNowRow_all[num]:
        usedEn += df.iloc[i, 5]
        usedEn += eap * df.iloc[i, 3]
    return usedEn


def cntE(pathFromNowRow_all):
    remainE_copy = copy.deepcopy(remainE)
    for i in range(1, 5):
        remainE_copy[i] -= flyE(i, pathFromNowRow_all)
        remainE_copy[i] -= usedE(i, pathFromNowRow_all)
    return remainE_copy


def pathToMap():
    cnt1, cnt2, cnt3, cnt4 = 1, 1, 1, 1
    for i in pathFromNowRow_all_copy[1]:
        idx1t[cnt1] = i
        cnt1 += 1
        M1t.append((df.iloc[i, x_column], df.iloc[i, y_column]))
    for i in pathFromNowRow_all_copy[2]:
        idx2t[cnt2] = i
        cnt2 += 1
        M2t.append((df.iloc[i, x_column], df.iloc[i, y_column]))
    for i in pathFromNowRow_all_copy[3]:
        idx3t[cnt3] = i
        cnt3 += 1
        M3t.append((df.iloc[i, x_column], df.iloc[i, y_column]))
    for i in pathFromNowRow_all_copy[4]:
        idx4t[cnt4] = i
        cnt4 += 1
        M4t.append((df.iloc[i, x_column], df.iloc[i, y_column]))


def cntFixPlan(num):
    iandl = []
    for i in pathFromNowRow_all[num]:
        iandl.append((i, df.iloc[i, 4]))
        # remainE1[num] -= df.iloc[i, 5] + eap * df.iloc[i, 3]
    # remainE1[num] -= flyE(num, pathFromNowRow_all)
    iandl.sort(key=lambda x: x[1], reverse=True)
    for item in iandl:
        i = item[0]
        li = item[1]
        if i == nowPointRow[num]:
            if remainE1[num] >= df.iloc[i, 5] * (df.iloc[i, 3] - 1):
                return df.iloc[i, 3] - 1
            else:
                return remainE1[num] / df.iloc[i, 5]
        remainE1[num] -= df.iloc[i, 5] * (df.iloc[i, 3] - 1)
        if remainE1[num] <= 0:
            return 1
    return 0


def decideArea():
    fixPlan_all = [0]
    for i in range(1, 5):
        flyEng = flyE(i, pathFromNowRow_all)
        usedEn = 0
        for j in pathFromNowRow_all[i]:
            usedEn += df.iloc[j, 5] * df.iloc[j, 3]
            usedEn += eap * df.iloc[j, 3]
        # 如果够全部飞完
        if usedEn + flyEng <= remainE1[i]:
            fixPlan_all.append(df.iloc[nowPointRow[i], 3])
        # 如果不够全部修复
        else:
            fixPlan = cntFixPlan(i)
            fixPlan_all.append(fixPlan)
    return fixPlan_all


def ActionUAV():
    for i in range(1, 5):
        remainE[i] -= fixPlan_all[i] * df.iloc[nowPointRow[i], 5]
        # visit[allidx[i][nextPoint[i]]] = 1
        # fly to next point
        dis = math.sqrt((df.iloc[nowPointRow[i], x_column] - df.iloc[nextPoint[i], x_column]) ** 2 + (
                df.iloc[nowPointRow[i], y_column] - df.iloc[nextPoint[i], y_column]) ** 2)
        remainE[i] -= dis * EF
        nextPointRow[i] = allidx[i][nextPoint[i] + 1]


def centerRouting():
    allERemain = sum(remainE_copy)

    for i in range(1, 25):
        if visit[i] == 1:
            continue
        minDis = 999999999
        for j in range(1, 5):
            nowPointRowIndex = allidx[j][nowPoint[j] + 1]
            nowPoint_x = df.iloc[nowPointRowIndex, x_column]
            nowPoint_y = df.iloc[nowPointRowIndex, y_column]
            x_ = df.iloc[i, x_column]
            y_ = df.iloc[i, y_column]
            dis = math.sqrt((nowPoint_x - x_) ** 2 + (nowPoint_y - y_) ** 2)
            if dis < minDis:
                minDis = dis
                minIndex = j
        temp = []
        for j in range(1, 5):
            if j == minIndex:
                if i not in pathFromNowRow_all_copy[j]:
                    pathFromNowRow_all_copy[j].append(i)
            else:
                if i in pathFromNowRow_all_copy[j]:
                    pathFromNowRow_all_copy[j].remove(i)
    pathToMap()


def pathFromNowTopathFromNowRow(pathFromNow_all, pathFromNowRow_all, allidx):
    for i in range(1, 5):
        for j in pathFromNow_all[i]:
            pathFromNowRow_all[i].append(allidx[i][j + 1])


while True:
    nextPoint = [0] * 5
    path1 = [0, 3, 1, 5, 4, 2]
    path2 = [2, 4, 5, 1, 3, 0]
    path3 = [2, 3, 1, 4, 5, 0]
    path4 = [5, 2, 4, 3, 1, 0]
    pathall = [0, path1, path2, path3, path4]
    # for i in range(1,5):
    #     pathall.append(routing(MM[i],i).tolist())
    nextPointt = [0] * 5

    pathFromNow_all = [0] * 5
    for i in range(1, 5):
        pathFromNow_all[i] = printPath(i, pathall)

    remainE_copy = copy.deepcopy(remainE)

    M1t, M2t, M3t, M4t = [], [], [], []
    MMt = [0, M1t, M2t, M3t, M4t]
    idx1t, idx2t, idx3t, idx4t = {}, {}, {}, {}
    idxt_all = [0, idx1t, idx2t, idx3t, idx4t]

    pathFromNowRow_all = [[], [], [], [], []]

    pathFromNowRowt_all = [0, [], [], [], []]
    pathFromNowTopathFromNowRow(pathFromNow_all, pathFromNowRow_all, allidx)
    remainE1 = cntE(pathFromNowRow_all)

    pathFromNowRow_all_copy = copy.deepcopy(pathFromNowRow_all)
    centerRouting()
    nowPointRow = [0, idx1[nowPoint[1] + 1], idx2[nowPoint[2] + 1], idx3[nowPoint[3] + 1], idx4[nowPoint[4] + 1]]
    # path1t = routing(M1t, 1).tolist()
    path1t = [3, 4, 5, 0, 1, 7, 6, 2]
    # path2t = routing(M2t, 2).tolist()
    path2t = [2, 3, 1, 0]
    # path3t = routing(M3t, 3).tolist()
    path3t = [4, 5, 6, 7, 0, 1, 2, 3]
    # path4t = routing(M4t, 4).tolist()
    path4t = [1, 2, 3, 0]
    pathtall = [0, path1t, path2t, path3t, path4t]
    pathFromNowt_all = [0] * 5
    for i in range(1, 5):
        pathFromNowt_all[i] = printPatht(i, pathtall)
    pathFromNowTopathFromNowRow(pathFromNowt_all, pathFromNowRowt_all, idxt_all)
    remainE2 = cntE(pathFromNowRowt_all)
    sumOfRemainE1 = sum(remainE1)
    sumOfRemainE2 = sum(remainE2)
    if sumOfRemainE2 < sumOfRemainE1:
        nextPoint = nextPoint
        pathFromNowRow_all = copy.deepcopy(pathFromNowRowt_all)
        remainE1 = copy.deepcopy(remainE2)
        pathFromNow_all = copy.deepcopy(pathFromNowt_all)
        allidx = copy.deepcopy(idxt_all)

    # 计算num号无人机修复计划

    fixPlan_all = decideArea()
    nextPointRow = [0] * 5

    MM = [[], [], [], [], []]
    ActionUAV()
    for i in range(1, 5):
        for j in pathFromNowRow_all[i]:
            if visit[j] == 0:
                MM[i].append((df.iloc[j, x_column], df.iloc[j, y_column]))
    allidx = [0, {}, {}, {}, {}]
    for i in range(1, 5):
        cnt = 0
        for j in range(len(pathFromNowRow_all[i])):
            n = pathFromNowRow_all[i][j]
            if visit[n] == 0:
                MM[i].append((df.iloc[n, x_column], df.iloc[n, y_column]))
                allidx[i][cnt] = n
                cnt += 1

    print(fixPlan_all)
    print(remainE)


def test():
    cfg = load_pkl('Pkl/test6.pkl')
    env = Env_tsp(cfg)

    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    # Convert the input list or array to a PyTorch tensor
    nodes = torch.tensor(M1, dtype=torch.float32, device=device)
    print(env.get_tour_distance(nodes, torch.tensor(
        [1, 5, 4, 2, 0, 3], dtype=torch.long, device=device)))
# test()
