import matplotlib.pyplot as plt
import numpy as np
def plotObj(obj_list):
    # plt.rcParams['font.sans-serif'] = ['SimHei'] #show chinese
    # plt.rcParams['axes.unicode_minus'] = False   # Show minus sign
    plt.plot(np.arange(1,len(obj_list)+1),obj_list)
    plt.xlabel('Iterations')
    plt.ylabel('Obj Value')
    plt.grid()
    plt.xlim(1,len(obj_list)+1)
    plt.show()