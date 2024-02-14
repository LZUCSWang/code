import math
def calDistance(route,model):
    '''计算行驶距离
    route:需求节点seq_no有序排列集合。
    model:存储算法参数。
    '''
    distance = []
    depot = model.depot
    for i in range(len(route)-1): # 每一段的行驶距离计算，路段为节点数目减1
        from_node = model.node_list[route[i]] # 获得起始节点
        to_node = model.node_list[route[i+1]] # 下一个节点
        distance.append(math.sqrt((from_node.x_coord-to_node.x_coord)**2+(from_node.y_coord-to_node.y_coord)**2)) # 欧氏距离计算
    first_node = model.node_list[route[0]]
    last_node = model.node_list[route[-1]]
    distance.insert(0,math.sqrt((depot.x_coord-first_node.x_coord)**2+(depot.y_coord-first_node.y_coord)**2))
    distance.append(math.sqrt((depot.x_coord-last_node.x_coord)**2+(depot.y_coord - last_node.y_coord)**2))
    return distance
def calObj(nodes_seq,model):
    '''得到当前无人机的行驶距离以及目标值。
    nodes_seq:需求节点seq_no有序排列集合。
    model:存储算法参数。
    '''
    distance = calDistance(nodes_seq,model)
    obj = 0
    for i in nodes_seq:
        obj+= model.node_list[i].restored_area
    return distance,obj