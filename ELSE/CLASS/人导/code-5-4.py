#code-4-4.py
#Multiple Linear Regression
from sklearn.datasets import load_boston
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
from sklearn. model_selection import train_test_split

dataset = load_boston()
x_data = dataset.data # 导入所有特征变量
y_data = dataset.target # 导入目标值（房价）
name_data = dataset.feature_names #导入特征

x_train,x_test,y_train,y_test = train_test_split(x_data, y_data,test_size= 0.25,random_state= 1001)

mlr_model = LinearRegression() #创建线性回归估计器实例
mlr_model.fit(x_train,y_train)#用训练数据拟合模型
y_test_p = mlr_model.predict(x_test)#用训练的模型对测试集进行预测

plt.subplot(1, 1, 1)
plt.scatter(x_test[:,5],y_test,s = 20, color="r")
plt.scatter(x_test[:,5],y_test_p,s = 20, color="b")
plt.xlabel('Room Number')
plt.ylabel('Price')
plt.title(name_data[5])  
plt.show()

r_squared = mlr_model.score(x_test, y_test)
print('R2 = %s' %r_squared )
