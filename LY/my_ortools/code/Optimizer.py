import random
import numpy as np
import copy
import math
from itertools import combinations
import pandas  as pd
from datetime import datetime
from Plotobj import plotObj

def get_num(proba):
    """
    生成一个随机数，这个随机数小于这个概率就返回1，否则返回0。可见，概率越大，返回1的可能性就越大。
    proba: [0, 1]之间（但包括）的数字 - 1的概率
    """
    random.seed(datetime.now())
    if random.random() < proba:
        return 1
    return 0

def get_area(point):
    '''
    计算每一个待修复区域的已修复面积。
    point:某一个修复区域。
    '''
    area=0
    for i,j in enumerate(point):
        area+=(2**(i))*j
    return area


def check(model,child,sol,g=9.8,h=6,r=1.204,s=0.2,M=1.5,eap=10,k=1):
    '''
    检查是否满足约束。
    model:存储算法参数。
    child:某个生成的多维背包的解。
    sol:整个协同过程的解。
    '''
    Es = 0
    Eap = 0
    Ef = 0
    Q = 0
    for i,j in enumerate(child):
        qi = k*(1+model.node_list[i].level)**3
        Q+=get_area(j)*qi
    for i,j in enumerate(child):
        q = k*(1+model.node_list[i].level)**3
        e = ((M+q)**(3/2))*math.sqrt((g**3)/(2*r*s*h))
        Es+=get_area(j)*e
        Eap+=eap*get_area(j)
    eij = [((M+Q)**(3/2))*math.sqrt((g**3)/(2*r*s*h))]
    temp = Q
    for i in sol.nodes_seq:
        temp = temp-get_area(child[i])*(k*(1+model.node_list[i].level)**3)
        eij.append(((M+temp)**(3/2))*math.sqrt((g**3)/(2*r*s*h)))
    for i,j in enumerate(sol.distance):
        Ef+=eij[i]*j
    E = Es+Eap+Ef
    if Es+Eap+Ef<=model.max_energy:
        return True,E
    else:
        return False,E

def put_one(population,model):
    '''
    由于在修复等级[0.3,0.8]中的节点至少修复1个单位面积，所以此函数用于修复单个面积。
    population:多为背包问题的种群。
    model:存储算法参数。
    '''
    for i,j in enumerate(population):
        for index,k in enumerate(j):
            if model.node_list[index].level<0.3 or model.node_list[index].level>0.8:
                population[i][index][0] = 0
            else:
                population[i][index][0] = 1

    return  population

def get_zeropoint(nodes_seq,model):

    zero_point=[]
    for index in nodes_seq:
        if model.node_list[index].level<0.3 or model.node_list[index].level>0.8:
            zero_point.append(index)

    return  zero_point


def optimize(learn_rate, pop_size, num_best_vec_to_update_from,model,sol,max_area,
             optimisation_cycles, eval_f, eps=0.01, vec_storage=None):
    """
    PBIL算法。
    learn_rate：将种群向量（vec）推向每个最佳个体的速度。
    pop_size: 种群中的个体数量
    num_best_vec_to_update_from: 多少个最佳个体将被用于更新种群向量。
    sol:整个协同过程的解。
    max_area:所有待修复区域中的最大待修复面积。
    optimisation_cycles：优化周期的数量。
    eval_f：用于个体评估的函数。
    eps:将被推离极端值（0，1）的eps。
    vec_storage：用于存储每个回合的种群向量，应实现 "append "方法。
    返回：最佳二进制向量。如果许多向量具有相同的适配度，则返回最早期出现的那个。
    """
    history=[]
    max_bit = len(bin(max_area)[2:])
    zero_point = get_zeropoint(sol.nodes_seq,model)
    nodes_seq = copy.deepcopy(sol.nodes_seq)
    for i in zero_point:
        nodes_seq.remove(i)
    np.set_printoptions(threshold=np.inf)
    population = np.zeros((pop_size, len(sol.nodes_seq), max_bit))
    population_one = copy.deepcopy(put_one(population, model))
    # 概率向量初始化
    # vec = np.full((len(sol.nodes_seq), max_bit), 1, dtype=float)
    # ===================================
    vec = np.full((len(sol.nodes_seq), max_bit), 0, dtype=float)
    bit_array=[2**(i) for i in range(max_bit)]
    range_array = np.array(bit_array).cumsum()
    for i in nodes_seq:
        for index,j in enumerate(range_array):
            if model.node_list[i].areas<=j:
                vec[:index+1]=float(1/model.node_list[i].areas)
    #====================================
    # 给每一向量一个初始化得分为None
    scores = [None for _ in range(pop_size)]
    # 初始化一个最佳的结果
    best_of_all = [-float("inf"), None]
    # 判断是否要存储向量 （就是把之前历史的向量变化规律存下来）
    if vec_storage is not None:
        vec_storage.append(list(vec))
    # 迭代优化，optimisation_cycles为迭代次数
    count=0
    for i in range(optimisation_cycles):
        # print('optimisation_cycles: ',i)
        # 解决方案向量的生成
        for j in range(pop_size):
            # 对于每一个种群个体
            for k in nodes_seq:
                for l in range(max_bit):
                # 根据概率去给每一个种群的每一个基因位设置值，注意这个概率的向量只有一个，多样性决绝于get_num里面的随机数
                    population[j][k][l] = get_num(vec[k][l])
                if get_area(population[j][k])==0:
                    population[j][k][0]=1
            if check(model, population[j], sol)[0]==False:
                reverse_flag = True
                while reverse_flag:
                    for n in nodes_seq:
                        if get_area(population[j][n])==1:
                            continue
                        num = len(bin(int(get_area(population[j][n])-1))[2:])
                        population[j][n][:num]=list(reversed(bin(int(get_area(population[j][n])-1))[2:]))
                        population[j][n][num:]=0
                    if check(model, population[j], sol)[0]:
                        reverse_flag = False
                    if (check(model, population[j], sol)[0]==False) and (population==population_one).all():
                        # print('The energy constraint cannot be met and the energy required is at least greater than :',check(model, population[j], sol)[1])
                        return None,0
            for n in nodes_seq:
                if get_area(population[j][n]) > model.node_list[n].areas:
                    reverse_flag = True
                    while reverse_flag:
                        num = len(bin(int(get_area(population[j][n]) - 1))[2:])
                        population[j][n][:num] = list(reversed(bin(int(get_area(population[j][n]) - 1))[2:]))
                        population[j][n][num:] = 0
                        if get_area(population[j][n])<=model.node_list[n].areas:
                            reverse_flag = False
            # print('The remained energy:',model.max_energy-check(model, population[j], sol)[1])
            scores[j] = eval_f(population[j],get_area)
        array_scores = np.array(scores)
        max_one = array_scores.argmax()
        # ==========================================================================================
        # 单点 局部
        new_seq = sorted(nodes_seq, key=lambda x: model.node_list[x].level, reverse=False)
        if check(model, population[max_one], sol)[0]:
            select_seq = [new_seq[count]]
            count+=1
            # print(count)
            for n in select_seq:
                while True:
                    temp = copy.deepcopy(population[max_one][n])
                    num = len(bin(int(get_area(population[max_one][n])+1))[2:])
                    population[max_one][n][:num] = list(reversed(bin(int(get_area(population[max_one][n]) + 1))[2:]))
                    population[max_one][n][num:] = 0
                    if get_area(population[max_one][n]) <= model.node_list[n].areas and check(model,
                                                                                                  population[max_one],
                                                                                                  sol)[0]:
                            # pass
                        break
                    else:
                        population[max_one][n] = temp
                        break

        if count == len(new_seq):
            count = 0
        # ========================================================================================================================================
        scores[max_one] = eval_f(population[max_one],get_area)
        # 根据目标值函数的得分，对种群进行从大到小的排序
        sorted_res = sorted(zip(scores, population), key=lambda x: x[0], reverse=True)
        # 选出最好的几个
        best = sorted_res[:num_best_vec_to_update_from]
        # 更新最好的解决方案
        if best_of_all[0] < best[0][0]:
            best_of_all = (best[0][0], list(best[0][1]))
            sol.obj = best[0][0]
            for ij in sol.nodes_seq:
                model.node_list[ij].restored_area = get_area(best_of_all[1][ij])
        history.append(best_of_all[0])
        x = np.array([i[1] for i in best])
        for k in nodes_seq:
            for l in range(max_bit):
                sum_ij=0
                for ij in x:
                    sum_ij+=ij[k][l]
                vec[k][l] = (1-learn_rate)*vec[k][l]+learn_rate*(1/num_best_vec_to_update_from)*(sum_ij)
        # 如果概率超出了[0,1]范围，就对它进行修正
        for k in nodes_seq:
            for l in range(max_bit):
                if vec[k][l] < 0:
                    vec[k][l] = 0 + eps
                elif vec[k][l] > 1:
                    vec[k][l] = 1 - eps
        # 判断是否要存储这个向量，存储的意义是保留这个向量的历史更新记录
        if vec_storage is not None:
            vec_storage.append(list(vec))
    print(history)
    # plotObj(history)  # 可省略
    return best_of_all[1], best_of_all[0],history

def Iterated_Local_Search_optimize(learn_rate, pop_size, num_best_vec_to_update_from,model,sol,max_area,
             optimisation_cycles, eval_f, eps=0.01, vec_storage=None):
    history = []
    max_bit = len(bin(max_area)[2:])
    zero_point = get_zeropoint(sol.nodes_seq, model)
    nodes_seq = copy.deepcopy(sol.nodes_seq)
    for i in zero_point:
        nodes_seq.remove(i)
    np.set_printoptions(threshold=np.inf)
    # 向量初始化，长度就是基因位数，即数据集个数的长度，每个基因位数概率复制为0.5
    vec = np.full((len(sol.nodes_seq), max_bit), 1, dtype=float)
    population = np.zeros((pop_size, len(sol.nodes_seq), max_bit))
    population_one = copy.deepcopy(put_one(population, model))
    # ===================================
    # vec = np.full((len(sol.nodes_seq), max_bit), 0, dtype=float)
    # bit_array=[2**(i) for i in range(max_bit)]
    # range_array = np.array(bit_array).cumsum()
    # for i in nodes_seq:
    #     for index,j in enumerate(range_array):
    #         if model.node_list[i].areas<=j:
    #             vec[:index+1]=float(1/model.node_list[i].areas)
    # ====================================
    # 给每一向量一个初始化得分为None
    scores = [None for _ in range(pop_size)]
    # 初始化一个最佳的结果
    best_of_all = [-float("inf"), None]
    # 判断是否要存储向量 （就是把之前历史的向量变化规律存下来）
    if vec_storage is not None:
        vec_storage.append(list(vec))
    # 迭代优化，optimisation_cycles为迭代次数
    count=0
    for j in range(pop_size):
        # 对于每一个种群个体
        for k in nodes_seq:
            for l in range(max_bit):
                # 根据概率去给每一个种群的每一个基因位设置值，注意这个概率的向量只有一个，多样性决绝于get_num里面的随机数
                population[j][k][l] = get_num(vec[k][l])
            if get_area(population[j][k]) == 0:
                population[j][k][0] = 1
    for i in range(optimisation_cycles):
        # print('optimisation_cycles: ', i)
        # 解决方案向量的生成
        for j in range(pop_size):
            if check(model, population[j], sol)[0] == False:
                reverse_flag = True
                while reverse_flag:
                    for n in nodes_seq:
                        if get_area(population[j][n]) == 1:
                            continue
                        num = len(bin(int(get_area(population[j][n]) - 1))[2:])
                        population[j][n][:num] = list(reversed(bin(int(get_area(population[j][n]) - 1))[2:]))
                        population[j][n][num:] = 0
                    if check(model, population[j], sol)[0]:
                        reverse_flag = False
                    if (check(model, population[j], sol)[0] == False) and (population == population_one).all():
                        print(check(model, population[j], sol)[1])
                        return None, 0
            for n in nodes_seq:
                if get_area(population[j][n]) > model.node_list[n].areas:
                    reverse_flag = True
                    while reverse_flag:
                        num = len(bin(int(get_area(population[j][n]) - 1))[2:])
                        population[j][n][:num] = list(reversed(bin(int(get_area(population[j][n]) - 1))[2:]))
                        population[j][n][num:] = 0
                        if get_area(population[j][n]) <= model.node_list[n].areas:
                            reverse_flag = False
            # print('The remained energy:',model.max_energy-check(model, population[j], sol)[1])
            scores[j] = eval_f(population[j], get_area)
        array_scores = np.array(scores)
        max_one = array_scores.argmax()
        # ==========================================================================================
        # 单点 局部
        new_seq = sorted(nodes_seq, key=lambda x: model.node_list[x].level, reverse=False)
        if check(model, population[max_one], sol)[0]:
            select_seq = [new_seq[count]]
            count += 1
            for n in select_seq:
                while True:
                    temp = copy.deepcopy(population[max_one][n])
                    num = len(bin(int(get_area(population[max_one][n]) + 1))[2:])
                    population[max_one][n][:num] = list(reversed(bin(int(get_area(population[max_one][n]) + 1))[2:]))
                    population[max_one][n][num:] = 0
                    if get_area(population[max_one][n]) <= model.node_list[n].areas and check(model,
                                                                                              population[max_one],
                                                                                              sol)[0]:
                        # pass
                        break
                    else:
                        population[max_one][n] = temp
                        break

        if count == len(new_seq):
            count = 0
        # ========================================================================================================================================
        scores[max_one] = eval_f(population[max_one], get_area)
        # 根据目标值函数的得分，对种群进行从大到小的排序
        sorted_res = sorted(zip(scores, population), key=lambda x: x[0], reverse=True)
        # 选出最好的几个
        best = sorted_res[:num_best_vec_to_update_from]
        # 更新最好的解决方案
        if best_of_all[0] < best[0][0]:
            best_of_all = (best[0][0], list(best[0][1]))
            sol.obj = best[0][0]
            for ij in sol.nodes_seq:
                model.node_list[ij].restored_area = get_area(best_of_all[1][ij])
        history.append(best_of_all[0])
        # 判断是否要存储这个向量，存储的意义是保留这个向量的历史更新记录
        if vec_storage is not None:
            vec_storage.append(list(vec))
    print(history)
    # plotObj(history)  # 可省略
    return best_of_all[1], best_of_all[0],history