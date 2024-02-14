from Three_class import *
from File_read import readXlsxFile
from Actions import *
from Initialsol import genInitialSol
from Cal_target import *
from SA import sa_cooperation,sa_not_cooperation,sa_not_cooperation_notpbil,sa_cooperation_iterated
import numpy as np
import copy
from datetime import  datetime
from Plotobj import plotObj

def run(filepath,T0,Tf,detaT,energy,select):
    '''
    通过使用模拟退火算法一定程度解决车辆路径以及多维背包协同问题，运行逻辑程序。
    filepath:用于读取数据的文件的路径。
    T0:模拟退火算法中的"初始温度"。
    Tf:模拟退火算法中的"结束温度"。
    detaT:温度衰减的程度，用百分比表示。
    energy:无人机电池的能量。
    '''
    model = Model() # 存储算法参数
    model.max_energy = energy # 无人机的电池能量
    readXlsxFile(filepath,model) # 配置model以及各个node
    action_list = createActions(model.number_of_nodes) # 生成邻域
    history_best_obj = []
    sol = Sol()
    sol.nodes_seq = genInitialSol(model.node_seq_no_list) # 需求节点seq_no有序排列集合
    sol.distance,sol.obj = calObj(sol.nodes_seq,model) # 距离和，行驶路线
    model.best_sol = copy.deepcopy(sol) # 初始化最优解
    model.max_area = 10 # 节点的最大待修复面积
    Tk = T0
    nTk = len(action_list)# 内层循环为邻域元素数目
    history_pbil_obj=[]
    best_obj_list=[]
    tbe=datetime.now()
    # for i in range(1):
    for i in range(5):

        if select==1:
        # 协同优化
            history_best_obj=[]
            history_best_obj.append(sol.obj) # 存储历史最优解(协同优化)
            result=sa_cooperation(Tk,Tf,model,detaT,nTk,action_list,history_best_obj,copy.deepcopy(sol),local=True) # 模拟退火算法(协同优化)
            history_pbil_obj.append(history_best_obj)
            best_obj_list.append(result)
        if select==2:
        # 非协同优化
            history_best_obj.append(sum(sol.distance))  # 存储历史最优解(非协同优化)
            history,result= sa_not_cooperation(Tk, Tf, model, detaT, nTk, action_list, history_best_obj, sol) # 模拟退火算法(非协同优化)
            history_pbil_obj.append(history)
            best_obj_list.append(result)
        if select==3:
        # 非协同优化，采用iterated
            history_best_obj.append(sum(sol.distance))  # 存储历史最优解(非协同优化且不使用PBIL)
            history,result=sa_not_cooperation_notpbil(Tk, Tf, model, detaT, nTk, action_list, history_best_obj, sol,i)  # 模拟退火算法(非协同优化且不使用PBIL)
            history_pbil_obj.append(history)
            best_obj_list.append(result)
        if select == 4:
        # 协同优化 iterated
            history_best_obj = []
            history_best_obj.append(sol.obj)  # 存储历史最优解(协同优化)
            result = sa_cooperation_iterated(Tk, Tf, model, detaT, nTk, action_list, history_best_obj, sol)  # 模拟退火算法(协同优化)
            history_pbil_obj.append(history_best_obj)
            best_obj_list.append(result)
    ts=datetime.now()
    print(ts-tbe)
    if select==1:
        print("MEAN_HIS_OBJ:",np.array(history_pbil_obj).mean(axis=0))
        print("MEAN_MEAN_OBJ:",np.array(best_obj_list).mean())
        plotObj(np.array(history_pbil_obj).mean(axis=0))
        print("VAR:",np.array(best_obj_list).var())
        print("STD:",np.array(best_obj_list).std())
    if select==2:
        print("MEAN_HIS_OBJ:",np.array(history_pbil_obj).mean(axis=0))
        print("MEAN_MEAN_OBJ:",np.array(best_obj_list).mean())
        plotObj(np.array(history_pbil_obj).mean(axis=0))
        print("VAR:",np.array(best_obj_list).var())
        print("STD:",np.array(best_obj_list).std())
    if select==3:
        print("MEAN_HIS_OBJ:",np.array(history_pbil_obj).mean(axis=0))
        print("MEAN_MEAN_OBJ:",np.array(best_obj_list).mean())
        plotObj(np.array(history_pbil_obj).mean(axis=0))
        print("VAR:",np.array(best_obj_list).var())
        print("STD:",np.array(best_obj_list).std())
    if select==4:
        print("MEAN_HIS_OBJ:",np.array(history_pbil_obj).mean(axis=0))
        print("MEAN_MEAN_OBJ:",np.array(best_obj_list).mean())
        plotObj(np.array(history_pbil_obj).mean(axis=0))
        print("VAR:",np.array(best_obj_list).var())
        print("STD:",np.array(best_obj_list).std())

if __name__=='__main__':
    # for i in range(1,8):
    #     file = './data/CVRP/cvrp{}.xlsx'.format(i)
    file = './data/CVRP/cvrp1.xlsx'

    # file = '/home/stu_wxy/content/LY/my_sa_cvrp_pbil/SA_CVRP/data/CVRP/cvrp2.xlsx'
    # run(filepath=file,T0=6000,Tf=0.01,detaT=0.9,energy=10000000)
    result_get=run(filepath=file,T0=6000,Tf=0.01,detaT=0.9,energy=10000000,select=1)
    # run(filepath=file, T0=6000, Tf=0.01, detaT=0.9, energy=30000000)