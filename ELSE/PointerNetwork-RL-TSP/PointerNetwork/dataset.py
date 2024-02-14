import numpy as np  # 导入NumPy库，用于生成随机数据

class DataGenerator(object):

    # 初始化 DataGenerator
    def __init__(self, config):
        self.batch_size = config.batch_size  # 批处理大小
        self.max_length = config.max_length  # 最大序列长度

    # 生成用于训练过程的随机批次
    def train_batch(self):
        input_batch = []  # 存储输入批次的列表
        for _ in range(self.batch_size):
            # 生成随机的TSP实例
            input_ = self.gen_instance()
            # 存储批次
            input_batch.append(input_)
        return input_batch

    # 生成用于测试过程的随机批次
    def test_batch(self):
        # 生成随机的TSP实例
        input_ = self.gen_instance()
        # 使用NumPy的瓦片操作复制输入实例以构建整个批次
        input_batch = np.tile(input_, (self.batch_size, 1, 1))
        return input_batch

    # 生成随机的TSP-TW实例（旅行商问题-时间窗口）
    def gen_instance(self):
        # 随机生成城市的坐标，x和y坐标分别在1到100之间随机
        x = np.random.randint(low=1, high=100, size=(self.max_length, 1))
        y = np.random.randint(low=1, high=100, size=(self.max_length, 1))
        sequence = np.concatenate((x, y), axis=1)  # 将x和y坐标连接起来形成城市坐标序列

        return sequence  # 返回城市坐标序列作为TSP实例
