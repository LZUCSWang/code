from Three_class import *
from Actions import *
from Cal_target import *
from Plotobj import plotObj
from Output import outPut
from datetime import datetime
from Optimizer import optimize,Iterated_Local_Search_optimize,get_area
import random
import math
import copy
from tqdm import tqdm
<<<<<<< HEAD
from Optimizer import check
=======
>>>>>>> 49c4a71e4177a62bcfec99ea70ea85a9f307e999
def eval_fun(child,fun):
    '''
    目标值计算
    child:某个解。
    fun:函数。
    '''
    area=0
    for i in child:
          area+=fun(i)
    return area

def sa_cooperation(Tk,Tf,model,detaT,nTk,action_list,history_best_obj,sol,local):
    '''
    模拟退火算法(协同优化)
    Tk:模拟退火算法中的"温度"。
    Tf:模拟退火算法中的"初始温度"。
    model:存储算法参数。
    detaT:温度衰减的程度，用百分比表示。
    nTk:内循环次数，等于邻域大小。
    action_list:邻域。
    history_best_obj:历史最优解集合。
    sol:解。
    '''
    # history=[]
    TTk = Tk
    cnt=0
    while True:
        TTk*=detaT
        cnt+=1
        if TTk<Tf:
            break
    # while Tk>=Tf:
    for j in tqdm(range(cnt)):
        for i in range(nTk): # range(nTk)
            new_sol = Sol()
            new_sol.nodes_seq = doACtion(sol.nodes_seq, action_list[i]) # 打乱路线
            new_sol.distance, new_sol.obj = calObj(new_sol.nodes_seq, model)
            model_copy = copy.deepcopy(model)
            child,new_sol.obj,_ = optimize(learn_rate=0.2, pop_size=30, num_best_vec_to_update_from=6,model=model_copy,
                                     sol=new_sol,max_area=model.max_area, optimisation_cycles=150, eval_f=eval_fun, vec_storage=[],local_search=local)
            deta_f = new_sol.obj-sol.obj
            random.seed(datetime.now()) # 随机数种子，用于模拟退火的接纳策略
            if deta_f>0 or math.exp(deta_f/Tk)>random.random(): # 模拟退火的接纳策略
                sol = copy.deepcopy(new_sol) # 接纳新解
            if sol.obj>model.best_sol.obj:# 如果新解优于最优解，则更新最优解
                model.node_list = model_copy.node_list
                model.best_sol = copy.deepcopy(sol)
            # history.append(model.best_sol.obj)
        if detaT<1: # 退火温度衰减
            Tk = Tk* detaT # 外层循环衰减
        else:
            Tk = Tk - detaT
        history_best_obj.append(model.best_sol.obj)
        print("temperature：%s，cooperation local obj:%s best cooperation obj: %s" % (Tk,sol.obj,model.best_sol.obj))
        # print('---------------------------------the history:',history)
        # plotObj(history)

    print('Area convergence:',history_best_obj)
    print('sequence:',model.best_sol.nodes_seq)
    areas = []
    for i in model.best_sol.nodes_seq:
        areas.append(get_area(child[i]))
    print('areas:',areas)
    # plotObj(history_best_obj)
    print('------------------------------------------------------------------------------------------')
    return model.best_sol.obj
    # return history_best_obj
    # outPut(model)
def sa_cooperation_iterated(Tk,Tf,model,detaT,nTk,action_list,history_best_obj,sol):
    # history = []

    while Tk >= Tf:
        for i in range(nTk):  # range(nTk)
            new_sol = Sol()
            new_sol.nodes_seq = doACtion(sol.nodes_seq, action_list[i])  # 打乱路线
            new_sol.distance, new_sol.obj = calObj(new_sol.nodes_seq, model)
            model_copy = copy.deepcopy(model)
            child, new_sol.obj, _ =Iterated_Local_Search_optimize(learn_rate=0.2, pop_size=30, num_best_vec_to_update_from=6,
                                             model=model_copy,
                                             sol=new_sol, max_area=model.max_area, optimisation_cycles=150,
                                             eval_f=eval_fun, vec_storage=[])
            deta_f = new_sol.obj - sol.obj
            random.seed(datetime.now())
            if deta_f > 0 or math.exp(deta_f / Tk) > random.random():  # 模拟退火的接纳策略
                sol = copy.deepcopy(new_sol)
            if sol.obj > model.best_sol.obj:
                model.node_list = model_copy.node_list
                model.best_sol = copy.deepcopy(sol)
            # history.append(model.best_sol.obj)
        if detaT < 1:
            Tk = Tk * detaT  # 外层循环衰减
        else:
            Tk = Tk - detaT
        history_best_obj.append(model.best_sol.obj)
        # print("temperature：%s，cooperation local obj:%s best cooperation obj: %s" % (Tk,sol.obj,model.best_sol.obj))
        # print('---------------------------------the history:',history)
        # plotObj(history)

    print('Area convergence:', history_best_obj)
    print('sequence:', model.best_sol.nodes_seq)
    areas = []
    for i in model.best_sol.nodes_seq:
        areas.append(get_area(child[i]))
    print('areas:', areas)
    # plotObj(history_best_obj)
    print('------------------------------------------------------------------------------------------')
    return model.best_sol.obj
    # return history_best_obj
    # outPut(model)

def sa_not_cooperation(Tk,Tf,model,detaT,nTk,action_list,history_best_obj,sol):
    '''
    模拟退火算法(非协同优化)
    Tk:模拟退火算法中的"温度"。
    Tf:模拟退火算法中的"初始温度"。
    model:存储算法参数。
    detaT:温度衰减的程度，用百分比表示。
    nTk:内循环次数，等于邻域大小。
    action_list:邻域。
    history_best_obj:历史最优解集合。
    sol:解。
    '''
    while Tk>=Tf:
        for i in range(nTk): # range(nTk) 内循环
            new_sol = Sol()
            new_sol.nodes_seq = doACtion(sol.nodes_seq, action_list[i]) # 打乱路线
            new_sol.distance, new_sol.obj = calObj(new_sol.nodes_seq, model)
            deta_f = sum(new_sol.distance)-sum(sol.distance)
            random.seed(datetime.now())
            if deta_f<0 or math.exp(-deta_f/Tk)>random.random(): # 模拟退火的接纳策略
                sol = copy.deepcopy(new_sol)
            if sum(sol.distance)<sum(model.best_sol.distance):
                model.best_sol = copy.deepcopy(sol)
        if detaT<1:
            Tk = Tk* detaT # 外层循环衰减
        else:
            Tk = Tk - detaT
        history_best_obj.append(sum(model.best_sol.distance))
        print("temperature：{}，local distance:{} best distance: {}" .format(Tk,sum(sol.distance),sum(model.best_sol.distance)))
    print(history_best_obj)
    # plotObj(history_best_obj)
    print('sequence:',model.best_sol.nodes_seq)
    child, model.best_sol.obj,history = optimize(learn_rate=0.2, pop_size=30, num_best_vec_to_update_from=6, model=model,
                                  sol=model.best_sol, max_area=model.max_area, optimisation_cycles=150, eval_f=eval_fun,
                                  vec_storage=[],local_search=True)
    areas = []
    for i in model.best_sol.nodes_seq:
        areas.append(get_area(child[i]))
    print('areas:',areas)
    print('not cooperation obj:',model.best_sol.obj)
    return history,model.best_sol.obj
def sa_not_cooperation_notpbil(Tk,Tf,model,detaT,nTk,action_list,history_best_obj,sol,ii):
    '''
    模拟退火算法(非协同优化)
    Tk:模拟退火算法中的"温度"。
    Tf:模拟退火算法中的"初始温度"。
    model:存储算法参数。
    detaT:温度衰减的程度，用百分比表示。
    nTk:内循环次数，等于邻域大小。
    action_list:邻域。
    history_best_obj:历史最优解集合。
    sol:解。
    '''
    while Tk>=Tf:
        for i in range(nTk): # range(nTk)
            new_sol = Sol()
            new_sol.nodes_seq = doACtion(sol.nodes_seq, action_list[i]) # 打乱路线
            new_sol.distance, new_sol.obj = calObj(new_sol.nodes_seq, model)
            deta_f = sum(new_sol.distance)-sum(sol.distance)
            random.seed(datetime.now())
            if deta_f<0 or math.exp(-deta_f/Tk)>random.random(): # 模拟退火的接纳策略
                sol = copy.deepcopy(new_sol)
            if sum(sol.distance)<sum(model.best_sol.distance):
                model.best_sol = copy.deepcopy(sol)
        if detaT<1:
            Tk = Tk* detaT # 外层循环衰减
        else:
            Tk = Tk - detaT
        history_best_obj.append(sum(model.best_sol.distance))
        print("temperature：{}，local distance:{} best distance: {}" .format(Tk,sol.obj,sum(model.best_sol.distance)))
    print(history_best_obj)
    # plotObj(history_best_obj)
    print('sequence:', model.best_sol.nodes_seq)
    child, model.best_sol.obj,history = Iterated_Local_Search_optimize(learn_rate=0.2, pop_size=30, num_best_vec_to_update_from=6, model=model,
                                  sol=model.best_sol, max_area=model.max_area, optimisation_cycles=150, eval_f=eval_fun,
                                  vec_storage=[])
    areas = []
    for i in model.best_sol.nodes_seq:
        areas.append(get_area(child[i]))
    print('areas:',areas)
    print('not cooperation and not PBIL obj:',model.best_sol.obj)

    print(model.node_list)
    if(ii==29):
        _ = check(model,child,model.best_sol)
        for i in model.best_sol.nodes_seq:
            print(child[i])
    return history,model.best_sol.obj