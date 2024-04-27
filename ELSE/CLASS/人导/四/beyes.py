# !/usr/bin/env python
# coding: utf-8

# In[2]:


from sklearn.naive_bayes import GaussianNB
import numpy as np
import pandas as pd
from pandas import Series, DataFrame
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from matplotlib.colors import ListedColormap
# get_ipython().run_line_magic('matplotlib', 'inline')


# In[3]:


# 导入函数
muNB = GaussianNB()
# 读取数据
iris = load_iris()
# 取出数据中的data
data = iris.data
# 取出数据中的target
target = iris.target
# 取data中所有行前两列为训练数据
samples = data[:, :2]
print(samples)
# 训练数据
muNB.fit(samples, target)

# # 取出训练数据中第一列中的最大与最小值
xmin, xmax = samples[:, 0].min(), samples[:, 0].max()
# # 取出训练数据中第二列中的最大与最小值
ymin, ymax = samples[:, 1].min(), samples[:, 1].max()
# # 在最大与最小值的区间分成300个数据
x = np.linspace(xmin, xmax, 300)
y = np.linspace(ymin, ymax, 300)
# # 然后使这些数据组成一个平面
xx, yy = np.meshgrid(x, y)
# # 生成90000个坐标点
X_test = np.c_[xx.ravel(), yy.ravel()]
print(X_test)
# # 预测训练数据
y_ = muNB.predict(X_test)
# # 导入三种不同的颜色
colormap = ListedColormap(['#00aaff', '#aa00ff', '#ffaa00'])
# # 生成三个不同颜色的模块，第一列为x轴坐标，第二列为y轴坐标，预测之后，不同的点分成不同的三类
plt.title("Naive Bayesian algorithm")
plt.scatter(X_test[:, 0], X_test[:, 1], c=y_)


# In[5]:


# 生成训练数据生成的点的分布，c=target意思是根据target的值，生成不同的颜色的点
plt.title("Naive Bayesian algorithm")
plt.scatter(samples[:, 0], samples[:, 1], c=target, cmap=colormap)


# In[6]:


# 一起调用的话使两张图结合起来
plt.title("Naive Bayesian algorithm")
plt.scatter(X_test[:, 0], X_test[:, 1], c=y_)
plt.scatter(samples[:, 0], samples[:, 1], c=target, cmap=colormap)