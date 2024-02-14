<<<<<<< HEAD
# 导入所需的库
from sklearn.datasets import load_iris  # 导入加载iris数据集的函数
from sklearn import preprocessing  # 导入预处理模块
from sklearn.model_selection import train_test_split  # 导入划分训练集和测试集的函数
from sklearn.tree import DecisionTreeClassifier  # 导入决策树分类器
from sklearn.tree import export_graphviz  # 导入导出决策树可视化的函数
from six import StringIO  # 导入字符串IO模块
import pydotplus  # 导入pydotplus库用于处理dot格式数据
from IPython.display import display, Image  # 导入用于在IPython中显示图片的模块

# 加载数据集
iris = load_iris()  # 加载iris数据集

# 获取数据特征和目标变量
x = iris.data  # 数据特征，包含花朵的萼片长度、萼片宽度、花瓣长度、花瓣宽度
y = iris.target  # 目标变量，包含三个分类标签：0代表Setosa、1代表Versicolor、2代表Virginica

# 划分训练集和测试集
# 将数据集划分为训练集和测试集，其中测试集占总数据集的20%，随机种子为1，以确保结果的可复现性
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=1)

# 标准化训练集和测试集
scaler = preprocessing.StandardScaler().fit(x_train)  # 使用StandardScaler对训练集进行标准化
x1_train = scaler.transform(x_train)  # 对训练集进行标准化转换
x1_test = scaler.transform(x_test)  # 对测试集进行标准化转换

# 创建决策树分类器对象
clf = DecisionTreeClassifier(criterion='entropy')  # 使用信息熵作为划分标准

# 在训练集上训练决策树分类器
clf.fit(x_train, y_train)

# 在测试集上进行预测
y_pred = clf.predict(x1_test)

# 输出模型在测试集上的准确率
print(clf.score(x1_test, y_test))

# 设置环境变量以添加Graphviz的bin目录路径（用于生成决策树可视化）
import os
os.environ["PATH"] += os.pathsep + 'C:\\Program Files\\Graphviz 2.44\\bin'

# 创建字符串IO对象，用于保存决策树可视化的dot格式数据
dot_data = StringIO()

# 导出决策树可视化的dot格式数据
=======
#!/usr/bin/env python
# coding: utf-8

# In[1]:


from sklearn.datasets import load_iris
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import export_graphviz
from six import StringIO
import pydotplus
from IPython.display import display,Image


# In[2]:


iris=load_iris()
x=iris.data  #数据特征
y=iris.target#数据特征
x_train,x_test,y_train,y_test=train_test_split(x,y,test_size=0.2,random_state=1)
scaler=preprocessing.StandardScaler().fit(x_train)
x1_train=scaler.transform(x_train)
x1_test=scaler.transform(x_test)


# In[3]:


clf=DecisionTreeClassifier(criterion='entropy')
clf.fit(x_train,y_train)
y_pre=clf.predict(x1_test)
print(clf.score(x1_test,y_test))


# In[4]:


import os
os.environ["PATH"] += os.pathsep + 'C:\\Program Files\\Graphviz 2.44\bin'
dot_data=StringIO()
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
export_graphviz(clf,
                out_file=dot_data,
                feature_names=iris.feature_names,
                class_names=iris.target_names,
                filled=True,
                rounded=True,
                special_characters=True)
<<<<<<< HEAD

# 使用pydotplus解析dot数据，并创建决策树的图形对象
graph = pydotplus.graph_from_dot_data(dot_data.getvalue())

# 将决策树图形写入PNG文件
graph.write_png('iris.png')

# 在IPython中显示决策树图形
display(Image(graph.create_png()))
=======
graph=pydotplus.graph_from_dot_data(dot_data.getvalue())
graph.write_png('iris.png')
display(Image(graph.create_png()))


# In[ ]:





# In[ ]:





# In[ ]:




>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
