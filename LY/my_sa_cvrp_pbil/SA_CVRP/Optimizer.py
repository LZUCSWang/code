import random
import numpy as np
import copy
import math
from itertools import combinations
import pandas as pd
from datetime import datetime
from Plotobj import plotObj
from tqdm import tqdm
<<<<<<< HEAD

=======
>>>>>>> 49c4a71e4177a62bcfec99ea70ea85a9f307e999

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
    area = 0
    for i, j in enumerate(point):
        area += (2 ** (i)) * j
    return area

#eap,k
def check(model, child, sol, g=9.8, h=6, r=1.204, s=0.2, M=1.5, eap=10, k=1):
    '''
    检查某个种群是否满足约束。
    model:存储算法参数。
    child:某个生成的多维背包的解。
    sol:整个协同过程的解。
    '''
    Es = 0
    Eap = 0
    Ef = 0
    Q = 0
    for i, j in enumerate(child):
        qi = k * (1 + model.node_list[i].level) ** 3  # 3
        Q += get_area(j) * qi
    for i, j in enumerate(child):
        q = k * (1 + model.node_list[i].level) ** 3
        e = ((M + q) ** (3 / 2)) * math.sqrt((g ** 3) / (2 * r * s * h))# M+q
        Es += get_area(j) * e
        Eap += eap * get_area(j)
    eij = [((M + Q) ** (3 / 2)) * math.sqrt((g ** 3) / (2 * r * s * h))]
    temp = Q
    for i in sol.nodes_seq:
        temp = temp - get_area(child[i]) * (k * (1 + model.node_list[i].level) ** 3)
        eij.append(((M + temp) ** (3 / 2)) * math.sqrt((g ** 3) / (2 * r * s * h)))
    for i, j in enumerate(sol.distance):
        Ef += eij[i] * j
    E = Es + Eap + Ef
    if Es + Eap + Ef <= model.max_energy:
        return True, E
    else:
        return False, E
# def check(model, child, sol, g=9.8, h=6, r=1.024, s=0.2, M=1.5, eap=2e4, k=1e5):
#     Es = 0
#     Eap = 0
#     Ef = 0
#     Q = 0
#     for i, j in enumerate(child):
#         qi = k * (1 + model.node_list[i].level) ** 2  # 3
#         Q += get_area(j) * qi
#     for i, j in enumerate(child):
#         q = k * (1 + model.node_list[i].level) ** 2
#         e = (q ** (3 / 2)) * math.sqrt((g ** 3) / (2 * r * s * h))  # M+q
#         Es += get_area(j) * e
#         Eap += eap * get_area(j)
#     eij = [((M + Q) ** (3 / 2)) * math.sqrt((g ** 3) / (2 * r * s * h))]
#     temp = Q
#     for i in sol.nodes_seq:
#         temp = temp - get_area(child[i]) * (k * (1 + model.node_list[i].level) ** 3)
#         eij.append(((M + temp) ** (3 / 2)) * math.sqrt((g ** 3) / (2 * r * s * h)))
#     for i, j in enumerate(sol.distance):
#         Ef += eij[i] * j
#     E = Es + Eap + Ef
#     if Es + Eap + Ef <= model.max_energy:
#         return True, E
#     else:
#         return False, E


def put_one(population, model):
    '''
    由于在修复等级[0.3,0.8]中的节点至少修复1个单位面积，所以此函数用于修复单个面积。
    population:多维背包问题的种群。
    model:存储算法参数。
    '''
    for i, j in enumerate(population):
        for index, k in enumerate(j):
            if model.node_list[index].level < 0.3 or model.node_list[index].level > 0.8:
                population[i][index][0] = 0
            else:
                population[i][index][0] = 1

    return population


def get_zeropoint(nodes_seq, model):
    zero_point = []
    for index in nodes_seq:
        if model.node_list[index].level < 0.3 or model.node_list[index].level > 0.8:
            zero_point.append(index)

    return zero_point


def optimize(learn_rate, pop_size, num_best_vec_to_update_from, model, sol, max_area,
             optimisation_cycles, eval_f, local_search, eps=0.01, vec_storage=None):
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
    history = []
    max_bit = len(bin(max_area)[2:])
    zero_point = get_zeropoint(sol.nodes_seq, model)
    nodes_seq = copy.deepcopy(sol.nodes_seq)
    for i in zero_point:
        nodes_seq.remove(i)
    np.set_printoptions(threshold=np.inf)
    population = np.zeros((pop_size, len(sol.nodes_seq), max_bit))
    population_one = copy.deepcopy(put_one(population, model))
    # 概率向量初始化
    vec = np.full((len(sol.nodes_seq), max_bit), 1, dtype=float)
    # ===================================
    # vec = np.full((len(sol.nodes_seq), max_bit), 0, dtype=float)
    # bit_array=[2**(i) for i in range(max_bit)]
    # range_array = np.array(bit_array).cumsum()
    # for i in nodes_seq:
    #     for index,j in enumerate(range_array):
    #         if model.node_list[i].areas<=j:
    #             vec[:index+1]=float(1/model.node_list[i].areas)
<<<<<<< HEAD
=======
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
                while reverse_flag:#在while循环内通过基因位的翻转使得生成的解能够符合能量约束条件
                    for n in nodes_seq:
                        if get_area(population[j][n])==1:
                            continue
                        num = len(bin(int(get_area(population[j][n])-1))[2:])
                        population[j][n][:num]=list(reversed(bin(int(get_area(population[j][n])-1))[2:]))
                        population[j][n][num:]=0
                    if check(model, population[j], sol)[0]:
                        reverse_flag = False
                    if (check(model, population[j], sol)[0]==False) and (population==population_one).all():#无论怎么翻转都无法满足条件
                        # print('The energy constraint cannot be met and the energy required is at least greater than :',check(model, population[j], sol)[1])
                        return None,0,0
            for n in nodes_seq:
                if get_area(population[j][n]) > model.node_list[n].areas:#如果当前待修复区域的面积大于该区域的最大面积,则再进行二进制翻转操作，不可能我要修复的比原来的还要多
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
        max_one = array_scores.argmax() # 获取评分最高的一个点
        # ==========================================================================================
        # 单点 局部
        if local_search:# 尝试对评分最高的点通过打按照退化等级的重新排序进行进一步更新进化
            new_seq = sorted(nodes_seq, key=lambda x: model.node_list[x].level, reverse=False)# 将序列按照退化等级从小到大排序
            if check(model, population[max_one], sol)[0]:
                select_seq = [new_seq[count]] # 这里只选择了某一个唯一的待修复区域
                count+=1
                # print(count)
                for n in select_seq:# 遍历区域，对当前的选择的区域进行翻转尝试优化。
                    while True:
                        temp = copy.deepcopy(population[max_one][n])
                        num = len(bin(int(get_area(population[max_one][n])+1))[2:])
                        population[max_one][n][:num] = list(reversed(bin(int(get_area(population[max_one][n]) + 1))[2:]))
                        population[max_one][n][num:] = 0
                        if get_area(population[max_one][n]) <= model.node_list[n].areas and check(model,
                                                                                                      population[max_one],
                                                                                                      sol)[0]:#满足能量约束条件
                                # pass
                            break
                        else:
                            population[max_one][n] = temp#说明
                            break

            if count == len(new_seq):
                count = 0
        else:
            pass
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
    zero_point = get_zeropoint(sol.nodes_seq, model)#退化程度大于0.8或者小于0.3的节点
    nodes_seq = copy.deepcopy(sol.nodes_seq)
    for i in zero_point:
        nodes_seq.remove(i)
    np.set_printoptions(threshold=np.inf)#用于控制Python中小数的显示精度
    # 向量初始化，长度就是基因位数，即数据集个数的长度，每个基因位数概率复制为0.5
    vec = np.full((len(sol.nodes_seq), max_bit), 1, dtype=float)#初始化概率向量(15*4)
    population = np.zeros((pop_size, len(sol.nodes_seq), max_bit))
    population_one = copy.deepcopy(put_one(population, model))#put_one将修复等级大于0.8或者小于0.3的节点修复一个单位面积(至少一个)
    # ===================================
    # vec = np.full((len(sol.nodes_seq), max_bit), 0, dtype=float)
    # bit_array=[2**(i) for i in range(max_bit)]
    # range_array = np.array(bit_array).cumsum()
    # for i in nodes_seq:
    #     for index,j in enumerate(range_array):
    #         if model.node_list[i].areas<=j:
    #             vec[:index+1]=float(1/model.node_list[i].areas)
>>>>>>> 49c4a71e4177a62bcfec99ea70ea85a9f307e999
    # ====================================
    # 给每一向量一个初始化得分为None
    scores = [None for _ in range(pop_size)]
    # 初始化一个最佳的结果
    best_of_all = [-float("inf"), None]
    # 判断是否要存储向量 （就是把之前历史的向量变化规律存下来）
    if vec_storage is not None:
        vec_storage.append(list(vec))
    # 迭代优化，optimisation_cycles为迭代次数
<<<<<<< HEAD
    count = 0
    for i in range(optimisation_cycles):
        # print('optimisation_cycles: ',i)
        # 解决方案向量的生成
        for j in range(pop_size):
            # 对于每一个种群个体
            for k in nodes_seq:
                for l in range(max_bit):
                    # 根据概率去给每一个种群的每一个基因位设置值，注意这个概率的向量只有一个，多样性决绝于get_num里面的随机数
                    population[j][k][l] = get_num(vec[k][l])
                if get_area(population[j][k]) == 0:
                    population[j][k][0] = 1
            if check(model, population[j], sol)[0] == False:
                reverse_flag = True
                while reverse_flag:  # 在while循环内通过基因位的翻转使得生成的解能够符合能量约束条件
                    for n in nodes_seq:
                        if get_area(population[j][n]) == 1:
=======
    count=0
    #对每个种群分配一个初始解
    for j in range(pop_size):
        # 对于每一个种群个体
        for k in nodes_seq:
            # 对于每个待修复区域
            for l in range(max_bit):
                # 根据概率去给每一个种群的每一个基因位设置值，注意这个概率的向量只有一个，多样性决绝于get_num里面的随机数
                population[j][k][l] = get_num(vec[k][l])
            if get_area(population[j][k]) == 0:#如果随机分配后的结果为0,则修改为1
                population[j][k][0] = 1
    for i in tqdm(range(optimisation_cycles)):
        # print('optimisation_cycles: ', i)
        # 解决方案向量的生成
        for j in range(pop_size):
            if check(model, population[j], sol)[0] == False:#如果当前的个体不满足约束条件
                reverse_flag = True
                while reverse_flag:
                    for n in nodes_seq:#遍历所有的待修复区域,将所有的待修复区域的面积取值进行二进制翻转操作
                        if get_area(population[j][n]) == 1:#如果当前待修复区域的面积为1,则跳过
>>>>>>> 49c4a71e4177a62bcfec99ea70ea85a9f307e999
                            continue
                        num = len(bin(int(get_area(population[j][n]) - 1))[2:])
                        population[j][n][:num] = list(reversed(bin(int(get_area(population[j][n]) - 1))[2:]))#num前面的二进制翻转操作
                        population[j][n][num:] = 0# num后面的二进制置为0
                    if check(model, population[j], sol)[0]:#进行翻转后再次进行检查,如果满足约束条件,则退出循环
                        reverse_flag = False
<<<<<<< HEAD
                    if (check(model, population[j], sol)[0] == False) and (
                            population == population_one).all():  # 无论怎么翻转都无法满足条件
                        # print('The energy constraint cannot be met and the energy required is at least greater than :',check(model, population[j], sol)[1])
                        return None, 0, 0
            for n in nodes_seq:
                if get_area(population[j][n]) > model.node_list[
                    n].areas:  # 如果当前待修复区域的面积大于该区域的最大面积,则再进行二进制翻转操作，不可能我要修复的比原来的还要多
=======
                    if (check(model, population[j], sol)[0] == False) and (population == population_one).all():# 如果不满足约束条件且所有的待修复区域都只修复了一个单位面积,意思是在这种条件下哪怕都只修复1都不可能满足约束,说明这条路径太差了,则退出循环
                        print(check(model, population[j], sol)[1])
                        return None, 0
            for n in nodes_seq:#此时当前的个体(解)已经满足约束条件,再遍历每一个待修复区域,如果当前待修复区域的面积大于该区域的最大面积,则再进行二进制翻转操作
                if get_area(population[j][n]) > model.node_list[n].areas:
>>>>>>> 49c4a71e4177a62bcfec99ea70ea85a9f307e999
                    reverse_flag = True
                    while reverse_flag:
                        num = len(bin(int(get_area(population[j][n]) - 1))[2:])
                        population[j][n][:num] = list(reversed(bin(int(get_area(population[j][n]) - 1))[2:]))
                        population[j][n][num:] = 0
                        if get_area(population[j][n]) <= model.node_list[n].areas:
                            reverse_flag = False
<<<<<<< HEAD
            # print('The remained energy:',model.max_energy-check(model, population[j], sol)[1])
            scores[j] = eval_f(population[j], get_area)
        array_scores = np.array(scores)
        max_one = array_scores.argmax()  # 获取评分最高的一个点
        # ==========================================================================================
        # 单点 局部
        if local_search:  # 尝试对评分最高的点通过打按照退化等级的重新排序进行进一步更新进化
            new_seq = sorted(nodes_seq, key=lambda x: model.node_list[x].level, reverse=False)  # 将序列按照退化等级从小到大排序
            if check(model, population[max_one], sol)[0]:
                select_seq = [new_seq[count]]  # 这里只选择了某一个唯一的待修复区域
                count += 1
                # print(count)
                for n in select_seq:  # 遍历区域，对当前的选择的区域进行翻转尝试优化。
                    while True:
                        temp = copy.deepcopy(population[max_one][n])
                        num = len(bin(int(get_area(population[max_one][n]) + 1))[2:])
                        population[max_one][n][:num] = list(
                            reversed(bin(int(get_area(population[max_one][n]) + 1))[2:]))
                        population[max_one][n][num:] = 0
                        if get_area(population[max_one][n]) <= model.node_list[n].areas and \
                                check(model, population[max_one], sol)[0]:  # 满足能量约束条件
                            # pass
                            break
                        else:
                            population[max_one][n] = temp  # 说明
                            break
=======
            print('The remained energy:',model.max_energy-check(model, population[j], sol)[1])#目前的是完全合法的一个解
            scores[j] = eval_f(population[j], get_area)
        array_scores = np.array(scores)
        max_one = array_scores.argmax()#返回最大值的索引,即最大值的下标
        # ==========================================================================================
        # 单点 局部
        new_seq = sorted(nodes_seq, key=lambda x: model.node_list[x].level, reverse=False)#按照节点的退化程度进行排序,从小到大,即从退化程度小的开始修复,因为退化程度小的节点的面积较小,所以修复的面积也较小,这样可以保证能够修复更多的节点
        if check(model, population[max_one], sol)[0]:#检查max_one个体是否满足约束条件
            select_seq = [new_seq[count]]
            count += 1
            for n in select_seq:
                while True:
                    temp = copy.deepcopy(population[max_one][n])
                    num = len(bin(int(get_area(population[max_one][n]) + 1))[2:])#当前待修复区域的面积加1后的二进制位数,为什么要+1,因为至少修复一个单位面积
                    population[max_one][n][:num] = list(reversed(bin(int(get_area(population[max_one][n]) + 1))[2:]))# num前面的二进制翻转操作
                    population[max_one][n][num:] = 0# num后面的二进制置为0
                    if get_area(population[max_one][n]) <= model.node_list[n].areas and check(model,
                                                                                              population[max_one],
                                                                                              sol)[0]:#如果当前待修复区域的面积小于等于该区域的最大面积且满足约束条件,则退出循环
                        # pass
                        break
                    else:
                        population[max_one][n] = temp#否则将当前待修复区域的面积还原为temp,即当前待修复区域本来的面积
                        break
>>>>>>> 49c4a71e4177a62bcfec99ea70ea85a9f307e999

            if count == len(new_seq):
                count = 0
        else:
            pass
        # ========================================================================================================================================
        scores[max_one] = eval_f(population[max_one], get_area)
        # 根据目标值函数的得分，对种群进行从大到小的排序
        sorted_res = sorted(zip(scores, population), key=lambda x: x[0], reverse=True)
        # 选出最好的几个
        best = sorted_res[:num_best_vec_to_update_from]
        # 更新最好的解决方案
        if best_of_all[0] < best[0][0]:#更新best_of_all
            best_of_all = (best[0][0], list(best[0][1]))
            sol.obj = best[0][0]
            for ij in sol.nodes_seq:
                model.node_list[ij].restored_area = get_area(best_of_all[1][ij])#更新每个节点的已修复面积
        history.append(best_of_all[0])
        x = np.array([i[1] for i in best])
        for k in nodes_seq:
            for l in range(max_bit):
                sum_ij = 0
                for ij in x:
                    sum_ij += ij[k][l]
                vec[k][l] = (1 - learn_rate) * vec[k][l] + learn_rate * (1 / num_best_vec_to_update_from) * (sum_ij)
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
    # print(history)
    # plotObj(history)  # 可省略
    return best_of_all[1], best_of_all[0], history


def Iterated_Local_Search_optimize(learn_rate, pop_size, num_best_vec_to_update_from, model, sol, max_area,
                                   optimisation_cycles, eval_f, eps=0.01, vec_storage=None):
    history = []
    max_bit = len(bin(max_area)[2:])
    zero_point = get_zeropoint(sol.nodes_seq, model)  # 退化程度大于0.8或者小于0.3的节点
    nodes_seq = copy.deepcopy(sol.nodes_seq)
    for i in zero_point:
        nodes_seq.remove(i)
    np.set_printoptions(threshold=np.inf)  # 用于控制Python中小数的显示精度
    # 向量初始化，长度就是基因位数，即数据集个数的长度，每个基因位数概率复制为0.5
    vec = np.full((len(sol.nodes_seq), max_bit), 1, dtype=float)  # 初始化概率向量(15*4)
    population = np.zeros((pop_size, len(sol.nodes_seq), max_bit))
    population_one = copy.deepcopy(put_one(population, model))  # put_one将修复等级大于0.8或者小于0.3的节点修复一个单位面积(至少一个)
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
    count = 0
    # 对每个种群分配一个初始解
    for j in range(pop_size):
        # 对于每一个种群个体
        for k in nodes_seq:
            # 对于每个待修复区域
            for l in range(max_bit):
                # 根据概率去给每一个种群的每一个基因位设置值，注意这个概率的向量只有一个，多样性决绝于get_num里面的随机数
                population[j][k][l] = get_num(vec[k][l])
            if get_area(population[j][k]) == 0:  # 如果随机分配后的结果为0,则修改为1
                population[j][k][0] = 1
    for i in tqdm(range(optimisation_cycles)):
        # print('optimisation_cycles: ', i)
        # 解决方案向量的生成
        for j in range(pop_size):
            if check(model, population[j], sol)[0] == False:  # 如果当前的个体不满足约束条件
                reverse_flag = True
                while reverse_flag:
                    for n in nodes_seq:  # 遍历所有的待修复区域,将所有的待修复区域的面积取值进行二进制翻转操作
                        if get_area(population[j][n]) == 1:  # 如果当前待修复区域的面积为1,则跳过
                            continue
                        num = len(bin(int(get_area(population[j][n]) - 1))[2:])
                        population[j][n][:num] = list(
                            reversed(bin(int(get_area(population[j][n]) - 1))[2:]))  # num前面的二进制翻转操作
                        population[j][n][num:] = 0  # num后面的二进制置为0
                    if check(model, population[j], sol)[0]:  # 进行翻转后再次进行检查,如果满足约束条件,则退出循环
                        reverse_flag = False
                    if (check(model, population[j], sol)[0] == False) and (
                            population == population_one).all():  # 如果不满足约束条件且所有的待修复区域都只修复了一个单位面积,意思是在这种条件下哪怕都只修复1都不可能满足约束,说明这条路径太差了,则退出循环
                        print(check(model, population[j], sol)[1])
                        return None, 0
            for n in nodes_seq:  # 此时当前的个体(解)已经满足约束条件,再遍历每一个待修复区域,如果当前待修复区域的面积大于该区域的最大面积,则再进行二进制翻转操作
                if get_area(population[j][n]) > model.node_list[n].areas:
                    reverse_flag = True
                    while reverse_flag:
                        num = len(bin(int(get_area(population[j][n]) - 1))[2:])
                        population[j][n][:num] = list(reversed(bin(int(get_area(population[j][n]) - 1))[2:]))
                        population[j][n][num:] = 0
                        if get_area(population[j][n]) <= model.node_list[n].areas:
                            reverse_flag = False
            print('The remained energy:', model.max_energy - check(model, population[j], sol)[1])  # 目前的是完全合法的一个解
            scores[j] = eval_f(population[j], get_area)
        array_scores = np.array(scores)
        max_one = array_scores.argmax()  # 返回最大值的索引,即最大值的下标
        # ==========================================================================================
        # 单点 局部
        new_seq = sorted(nodes_seq, key=lambda x: model.node_list[x].level,
                         reverse=False)  # 按照节点的退化程度进行排序,从小到大,即从退化程度小的开始修复,因为退化程度小的节点的面积较小,所以修复的面积也较小,这样可以保证能够修复更多的节点
        if check(model, population[max_one], sol)[0]:  # 检查max_one个体是否满足约束条件
            select_seq = [new_seq[count]]
            count += 1
            for n in select_seq:
                while True:
                    temp = copy.deepcopy(population[max_one][n])
                    num = len(
                        bin(int(get_area(population[max_one][n]) + 1))[2:])  # 当前待修复区域的面积加1后的二进制位数,为什么要+1,因为至少修复一个单位面积
                    population[max_one][n][:num] = list(
                        reversed(bin(int(get_area(population[max_one][n]) + 1))[2:]))  # num前面的二进制翻转操作
                    population[max_one][n][num:] = 0  # num后面的二进制置为0
                    if get_area(population[max_one][n]) <= model.node_list[n].areas and check(model,
                                                                                              population[max_one],
                                                                                              sol)[
                        0]:  # 如果当前待修复区域的面积小于等于该区域的最大面积且满足约束条件,则退出循环
                        # pass
                        break
                    else:
                        population[max_one][n] = temp  # 否则将当前待修复区域的面积还原为temp,即当前待修复区域本来的面积
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
        if best_of_all[0] < best[0][0]:  # 更新best_of_all
            best_of_all = (best[0][0], list(best[0][1]))
            sol.obj = best[0][0]
            for ij in sol.nodes_seq:
                model.node_list[ij].restored_area = get_area(best_of_all[1][ij])  # 更新每个节点的已修复面积
        history.append(best_of_all[0])
        # 判断是否要存储这个向量，存储的意义是保留这个向量的历史更新记录
        if vec_storage is not None:
            vec_storage.append(list(vec))
    print(history)
    # plotObj(history)  # 可省略
    return best_of_all[1], best_of_all[0], history
