from Three_class import *
import pandas as pd

def readXlsxFile(filepath,model):
    '''将model以及node配置好。
    filepath:用于读取数据的文件的路径。
    model:存储算法参数。
    '''
    # 将基站数据放在xlsx文件的第一行。
    node_seq_no = -1 # 基站节点seq_no为-1，需求节点seq_no为0,1,2,...。
    df = pd.read_excel(filepath) # 读取文件
    for i in range(df.shape[0]):
        node = Node()
        node.id = node_seq_no # 物理节点id
        node.seq_no = node_seq_no # 物理节点映射id
        node.x_coord = df['x_coord'][i]
        node.y_coord = df['y_coord'][i]
        node.level=df['level'][i]
        node.areas=df['areas'][i]
        node.id=df['id'][i] # 文件中的id是从1开始的
        if df['level'][i] == -1:
            model.depot=node # 基站
        else:
            model.node_list.append(node) # 物理节点集合
            model.node_seq_no_list.append(node_seq_no)  # 物理节点映射id集合
        node_seq_no=node_seq_no+1
    model.number_of_nodes=len(model.node_list) # 除了基站的其他物理节点数量