#code-4-5.py
#SGD Multiple Linear Regression
from sklearn.datasets import load_boston
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import SGDRegressor
import matplotlib.pyplot as plt
from sklearn. model_selection import train_test_split

dataset = load_boston()
x_data = dataset.data # 导入所有特征变量
y_data = dataset.target # 导入目标值（房价）
name_data = dataset.feature_names #导入特征

x_train,x_test,y_train,y_test = train_test_split(x_data, y_data,test_size= 0.25,random_state= 1001)

# 分别初始化对特征和目标值的标准化器
sc_X = StandardScaler()
sc_y = StandardScaler()

# 分别对训练和测试数据的特征以及目标值进行标准化处理
x_train = sc_X.fit_transform(x_train)
x_test = sc_X.transform(x_test)

y_train = sc_y.fit_transform(y_train.reshape(-1, 1))
y_test = sc_y.transform(y_test.reshape(-1, 1))

#创建回归估计器实例,并选择残差平方和作为代价函数
sgd_model = SGDRegressor(loss='squared_loss', max_iter=250, verbose=1, learning_rate='constant', eta0=0.01)
sgd_model.fit(x_train,y_train)#用训练数据拟合模型
y_test_p = sgd_model.predict(x_test)#用训练的模型对测试集进行预测

r_squared = sgd_model.score(x_test, y_test)
print('R2 = %s' %r_squared )

plt.subplot(1, 1, 1)
y_test_p = sc_y.inverse_transform(y_test_p)
y_test = sc_y.inverse_transform(y_test)

plt.scatter(x_test[:,5],y_test_p,s = 20, color="b", marker='s')
plt.scatter(x_test[:,5],y_test,s = 20, color="r",marker='x')

plt.xlabel('Room Number')
plt.ylabel('Price')
plt.title(name_data[5])  
plt.show()

