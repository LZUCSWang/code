#code-4-1.py
#Visualize the linear relation between the
#number of room and the cost of the house.
from sklearn.datasets import load_boston
import matplotlib.pyplot as plt
dataset = load_boston()
x_data = dataset.data # 导入所有特征变量
y_data = dataset.target # 导入目标值（房价）
name_data = dataset.feature_names #导入特征
plt.subplot(1,1, 1)
plt.scatter(x_data[:,5],y_data,s = 20)
plt.plot([5.,8.5],[8.,48.], color='red',lw=3)
plt.xlabel('Room Number')
plt.ylabel('Price')
plt.title(name_data[5])  
for i in range(0, 20):
    print (x_data[i,5],y_data[i])
plt.show()
