from sklearn.neighbors import KNeighborsClassifier
import matplotlib.pyplot as plt
from sklearn.model_selection import cross_val_score
from sklearn.datasets import load_iris
# 读取鸢尾花数据集
iris = load_iris()
x = iris.data  # 特征数据
y = iris.target  # 目标数据

k_range = range(1, 31)  # 设置k值的范围
k_error = []  # 保存误差值

# 循环，取k=1到k=31，计算每个k值对应误差效果（炼丹）
for k in k_range:
    knn = KNeighborsClassifier(n_neighbors=k)  # 创建KNN分类器，设置k值
    # cv参数决定数据集划分比例，这里是按照5:1划分训练集和测试集
    # scoring参数设置评分方法为accuracy，verbose参数设置打印过程
    scores = cross_val_score(
        knn, x, y, cv=6, scoring='accuracy', verbose=1)  # 交叉验证
    # 保存误差值
    k_error.append(1 - scores.mean())  # 误差值=1-准确率
# 画图，x轴为k值[1,31]，y值为误差值
plt.plot(k_range, k_error)
plt.xlabel('Value of K for KNN')  # x轴标签
plt.ylabel('Error')  # y轴标签
plt.show()  # 显示图形
