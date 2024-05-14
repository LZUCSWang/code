import copy
import random
import datetime
def genInitialSol(node_seq):
    '''初始化节点顺序
    node_seq:需求节点seq_no有序排列集合。
    '''
    node_seq=copy.deepcopy(node_seq)
    # random.seed(datetim0e.time())
    random.seed(2) # 500*500 2 600*600 7 700*700 15 800*800 13 900*900 26 1000*1000 2
    random.shuffle(node_seq)
    return node_seq