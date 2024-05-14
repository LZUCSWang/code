class Sol():
    '''表示一个可行解'''
    def __init__(self):
        '''
        nodes_seq:需求节点seq_no有序排列集合，对应TSP的解
        obj:优化目标值
        distance:距离列表
        '''
        self.nodes_seq=None
        self.obj=0
        self.distance=0

class Node():
    '''表示一个修复区域'''
    def __init__(self):
        '''
        id:物理节点id，可选
        name:物理节点名称，可选
        seq_no:物理节点映射id，基地节点为-1，需求节点从0编号
        x_coord:物理节点x坐标
        y_coord:物理节点y坐标
        level:待修复等级
        areas:总的待修复单位圆数目
        recovery_area:修复单位圆矩阵
        '''
        self.id=0
        self.name=''
        self.seq_no=0
        self.x_coord=0
        self.y_coord=0
        self.level=0
        self.areas=0
        self.restored_area=0

class Model():
    '''存储算法参数'''
    def __init__(self):
        '''
        best_sol:全局最优解，值类型为Sol()
        node_list:物理节点集合，值类型为Node()
        node_seq_no_list:物理节点映射id集合
        depot:基站，值类型为Node()
        number_of_nodes:需求节点数量
        max_energy:无人机的电池容量
        max_area:对于待修复区域中最大的修复面积。
        '''
        self.best_sol=None
        self.node_list=[]
        self.node_seq_no_list=[]
        self.depot=None
        self.number_of_nodes=0
        self.max_energy=0
        self.max_area=0