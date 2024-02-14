import copy
def createActions(n):
    '''邻域生成
    n:节点数量。
    '''
    action_list = []
    nswap = n//2
    # 单点互相交换
    for i in range(nswap):
        action_list.append([1, i, i + nswap])

    # 2-opt
    for i in range(1, nswap):
        action_list.append([4, i, i + nswap])

    # or-opt
    for i in range(0, nswap, 2):
        action_list.append([5, i, i + nswap])

    # 两点互相交换
    for i in range(0, nswap, 2):
        action_list.append([2, i, i + nswap])
    # 队列顺序倒置
    for i in range(0, n, 4):
        action_list.append([3, i, i + 3])
    return action_list
def doACtion(nodes_seq,action):
    '''
    借用禁忌算法TS0中定义的算子
    nodes_seq:需求节点seq_no有序排列集合。
    action:定义的算子。
    '''
    nodes_seq=copy.deepcopy(nodes_seq)
    if action[0]==1:
        index_1 = action[1]
        index_2 = action[2]
        temporary = nodes_seq[index_1]
        nodes_seq[index_1] = nodes_seq[index_2]
        nodes_seq[index_2] = temporary
        return nodes_seq
    elif action[0]==2:
        index_1 = action[1]
        index_2 = action[2]
        temporary = [nodes_seq[index_1],nodes_seq[index_1+1]]
        nodes_seq[index_1] = nodes_seq[index_2]
        nodes_seq[index_1+1] = nodes_seq[index_2+1]
        nodes_seq[index_2] = temporary[0]
        nodes_seq[index_2+1] = temporary[1]
        return nodes_seq
    elif action[0]==3:
        index_1 = action[1]
        index_2 = action[2]
        nodes_seq[index_1:index_2+1] = list(reversed(nodes_seq[index_1:index_2+1]))
        return nodes_seq
    elif action[0]==4:
        index_1 = action[1]
        index_2 = action[2]
        temporary = nodes_seq[0:index_1+1]
        nodes_seq[0:index_1+1] = nodes_seq[(len(nodes_seq)//2):index_2+1]
        nodes_seq[(len(nodes_seq)//2):index_2+1] = temporary
        return nodes_seq
    elif action[0]==5:
        index_1 = action[1]
        index_2 = action[2]
        nodes_seq.insert(index_2+1,nodes_seq[index_1])
        nodes_seq.insert(index_2+2,nodes_seq[index_1+1])
        del nodes_seq[index_1]
        del nodes_seq[index_1]
        return nodes_seq