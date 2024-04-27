#code-4-2.py
#Simple Linear Regression
from sklearn.datasets import load_boston
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
from sklearn. model_selection import train_test_split

dataset = load_boston()
x_data = dataset.data # 导入所有特征变量
y_data = dataset.target # 导入目标值（房价）
name_data = dataset.feature_names #导入特征

x_train,x_test,y_train,y_test = train_test_split(x_data, y_data,test_size= 0.25,random_state= 1001)

x_data_train = x_train[:, 5].reshape(-1, 1)#选取前400个样本作为训练集
y_data_train = y_train.reshape(-1, 1)
x_data_test = x_test[:, 5].reshape(-1, 1)#选取剩余的样本作为训练集
y_data_test = y_test.reshape(-1, 1)


simple_model = LinearRegression() #创建线性回归估计器实例
simple_model.fit(x_data_train,y_data_train)#用训练数据拟合模型
y_data_test_p = simple_model.predict(x_data_test)#用训练的模型对测试集进行预测

print(simple_model.coef_, simple_model.intercept_)

plt.subplot(1, 1, 1)
plt.scatter(x_data_test,y_data_test,s = 20, color="r",marker="x")
plt.scatter(x_data_test,y_data_test_p,s = 20, color="b",marker="s")
plt.xlabel('Room Number')
plt.ylabel('Price')
plt.title(name_data[5])  
plt.show()
