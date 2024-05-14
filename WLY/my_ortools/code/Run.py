from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp
from Optimizer import optimize,Iterated_Local_Search_optimize,get_area
from File_read import readXlsxFile
from Three_class import *
from Cal_target import *
import pandas as pd
import numpy as np
import math
import copy
from Plotobj import plotObj

def create_data_model(filepath):
    data = dict()
    df = pd.read_excel(filepath)
    data['distance_matrix'] = np.zeros((df.shape[0],df.shape[0]))
    for i in range(df.shape[0]):
        for j in range(df.shape[0]):
            data['distance_matrix'][i][j]=math.sqrt((df['x_coord'][i]-df['x_coord'][j])**2+(df['y_coord'][i]-df['y_coord'][j])**2)
    data['num_vehicles'] = 1
    data['depot'] = 0
    return data


def print_solution(data, manager, routing, assignment):
    # 打印每辆车的路线(访问的位置)，以及路线的距离。
    route = []
    total_distance = 0
    for vehicle_id in range(data['num_vehicles']):
        index = routing.Start(vehicle_id)
        plan_output = 'The vehicle {}:\n'.format(vehicle_id + 1)
        route_distance = 0
        while not routing.IsEnd(index):
            node_index = manager.IndexToNode(index)
            plan_output += ' {0}  -> '.format(node_index)
            route.append(node_index)
            previous_index = index
            index = assignment.Value(routing.NextVar(index))
            route_distance += routing.GetArcCostForVehicle(
                previous_index, index, vehicle_id)
        plan_output += ' {0} \n'.format(manager.IndexToNode(index))
        plan_output += 'Total travel distance: {}m\n'.format(route_distance)
        print(plan_output)
        total_distance += route_distance
        return route

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

def main(energy,select):
    file = '../data/CVRP/cvrp2.xlsx'
    data = create_data_model(file)
    manager = pywrapcp.RoutingIndexManager(len(data['distance_matrix']),
                                           data['num_vehicles'], data['depot'])
    routing = pywrapcp.RoutingModel(manager)
    def distance_callback(from_index, to_index):
        from_node = manager.IndexToNode(from_index)
        to_node = manager.IndexToNode(to_index)
        return data['distance_matrix'][from_node][to_node]

    transit_callback_index = routing.RegisterTransitCallback(distance_callback)
    # 定义网络中各条边的成本
    routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)
    # 必须指定启发式方法来找到第一个可行解
    search_parameters = pywrapcp.DefaultRoutingSearchParameters()
    search_parameters.first_solution_strategy = (
        routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC)
    # 求解并打印结果
    assignment = routing.SolveWithParameters(search_parameters)
    if assignment:
        route = print_solution(data, manager, routing, assignment)
        route.remove(0)

    model = Model() # 存储算法参数
    model.max_energy = energy # 无人机的电池能量
    readXlsxFile(file,model) # 配置model以及各个node
    sol = Sol()
    sol.nodes_seq = list(np.array(route)-1)
    sol.distance,sol.obj = calObj(sol.nodes_seq,model) # 距离和，行驶路线
    model.best_sol = copy.deepcopy(sol) # 初始化最优解
    model.max_area = 10 # 节点的最大待修复面积
    obj_list=[]
    history_pbil_list=[]
    for i in range(5):
        if select ==0:
            child, obj,history_pbil = Iterated_Local_Search_optimize(learn_rate=0.2, pop_size=30, num_best_vec_to_update_from=6, model=model,
                                      sol=sol, max_area=model.max_area, optimisation_cycles=200, eval_f=eval_fun,
                                      vec_storage=[])
        else:

            child, obj,history_pbil = optimize(learn_rate=0.2, pop_size=30, num_best_vec_to_update_from=6, model=model,
                                  sol=sol, max_area=model.max_area, optimisation_cycles=200, eval_f=eval_fun,
                                  vec_storage=[])
        areas=[]
        for i in model.best_sol.nodes_seq:
            areas.append(get_area(child[i]))
        print(areas)
        print('not cooperation obj:',obj)
        print('---------------------------------------------------------------------------')
        history_pbil_list.append(history_pbil)
        obj_list.append(obj)
    print('MEAN_BESTOBJ:',np.array(obj_list).mean())
    print('MEAN_HISPBIL_OBJ:',np.array(history_pbil_list).mean(axis=0))
    plotObj(np.array(history_pbil_list).mean(axis=0))

if __name__ == '__main__':
    main(energy=10000000,select=1)