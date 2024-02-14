import tensorflow as tf
from tensorflow.contrib.rnn import LSTMCell

from decoder import Pointer_decoder  # 导入Pointer_decoder类
from critic import Critic  # 导入Critic类

class Actor(object):
    
    def __init__(self, config):
        self.config = config

        # Data config
        self.batch_size = config.batch_size  # 批处理大小
        self.max_length = config.max_length  # 输入序列长度（任务数）
        self.input_dimension = config.input_dimension  # 城市维度（坐标）

        # Network config
        self.input_embed = config.input_embed  # 嵌入空间维度
        self.num_neurons = config.hidden_dim  # 隐藏状态维度（LSTM单元）
        self.initializer = tf.contrib.layers.xavier_initializer()  # 变量初始化器

        # Training config (actor)
        self.global_step = tf.Variable(0, trainable=False, name="global_step")  # 全局步数
        # 创建tf的可训练变量，用于跟踪训练的全局步数，它是一个标量整数张量，每次使用优化器时都会增加1
        self.lr1_start = config.lr1_start  # 初始学习率
        self.lr1_decay_rate = config.lr1_decay_rate  # 学习率衰减率
        self.lr1_decay_step = config.lr1_decay_step  # 学习率衰减步数
        self.is_training = config.training_mode  # 训练模式标志

        # Training config (critic)
        self.global_step2 = tf.Variable(0, trainable=False, name="global_step2")  # 全局步数
        # 创建tf的可训练变量，用于跟踪训练的全局步数，它是一个标量整数张量，每次使用优化器时都会增加1
        self.lr2_start = config.lr1_start  # 初始学习率
        self.lr2_decay_rate = config.lr1_decay_rate  # 学习率衰减率
        self.lr2_decay_step = config.lr1_decay_step  # 学习率衰减步数

        # Tensor block holding the input sequences [Batch Size, Sequence Length, Features]
        self.input_ = tf.placeholder(tf.float32, [self.batch_size, self.max_length, self.input_dimension],
                                     name="input_raw")  # 输入数据占位符
        # 这段代码使用了TensorFlow中的placeholder方法。placeholder方法用于创建占位符，它是一种特殊的张量，用于在TensorFlow图中接收外部输入的数据。
        # 创建了一个名为input_raw的占位符。它的数据类型是tf.float32，形状是[self.batch_size, self.max_length, self.input_dimension]
        self.batch_idx = 0  # 批处理索引

        self.build_permutation()  # 构建排列
        self.build_critic()  # 构建评论家
        self.build_reward()  # 构建奖励
        self.build_optim()  # 构建优化器

    def build_permutation(self):
        with tf.variable_scope("encoder"):
        # 进入encoder作用域
            with tf.variable_scope("embedding"):
                # Embed input sequence
                W_embed = tf.get_variable("weights", [1, self.input_dimension, self.input_embed],
                                          initializer=self.initializer)  # 获取嵌入权重
                # 创建tf的可训练变量，用于嵌入输入序列，它的形状是[1, self.input_dimension, self.input_embed]
                embedded_input = tf.nn.conv1d(self.input_, W_embed, 1, "VALID", name="embedded_input")  # 卷积嵌入
                # Batch Normalization
                embedded_input = tf.layers.batch_normalization(embedded_input, axis=2, training=self.is_training,
                                                               name='layer_norm', reuse=None)  # 批处理标准化

            with tf.variable_scope("dynamic_rnn"):
                # Encode input sequence
                cell1 = LSTMCell(self.num_neurons, initializer=self.initializer)  # 创建LSTM单元
                # Return the output activations and last hidden state as tensors.
                encoder_output, encoder_state = tf.nn.dynamic_rnn(cell1, embedded_input, dtype=tf.float32)  # 动态RNN编码
                # 使用tf.nn.dynamic_rnn方法对嵌入后的输入进行动态RNN编码，得到编码后的输出encoder_output和最后一个隐藏状态encoder_state。
        with tf.variable_scope('decoder'):
            # Ptr-net returns permutations (self.positions), with their log-probability for backprop
            self.ptr = Pointer_decoder(encoder_output, self.config)  # 创建Pointer_decoder对象
            self.positions, self.log_softmax = self.ptr.loop_decode(encoder_state)  # 调用loop_decode方法

    def build_critic(self):
        with tf.variable_scope("critic"):
            # Critic predicts reward (parametric baseline for REINFORCE)
            self.critic = Critic(self.config)  # 创建Critic对象
            self.critic.predict_rewards(self.input_)  # 调用predict_rewards方法

    def build_reward(self):
        with tf.name_scope('permutations'):
            # Reorder input % tour
            self.permutations = tf.stack(
                [
                    tf.tile(tf.expand_dims(tf.range(self.batch_size, dtype=tf.int32), 1), [1, self.max_length + 1]),
                    self.positions
                ],
                2
            )
            # Sort
            self.ordered_input_ = tf.gather_nd(self.input_, self.permutations)  # 重新排列输入
            # [batch size, seq length + 1, features] to [features, seq length + 1, batch_size]
            self.ordered_input_ = tf.transpose(self.ordered_input_, [2, 1, 0])  # 转置

            # Ordered coordinates
            ordered_x_ = self.ordered_input_[0]  # 有序X坐标
            # [batch_size, seq length]        delta_x**2
            delta_x2 = tf.transpose(tf.square(ordered_x_[1:] - ordered_x_[:-1]), [1, 0])  # 计算X坐标差的平方
            ordered_y_ = self.ordered_input_[1]  # 有序Y坐标
            # [batch_size, seq length]        delta_y**2
            delta_y2 = tf.transpose(tf.square(ordered_y_[1:] - ordered_y_[:-1]), [1, 0])  # 计算Y坐标差的平方
            
        with tf.name_scope('environment'):
            # Get tour length (euclidean distance)
            inter_city_distances = tf.sqrt(delta_x2 + delta_y2)  # 欧几里得距离
            self.distances = tf.reduce_sum(inter_city_distances, axis=1)  # 距离求和 [batch_size]
            self.reward = tf.cast(self.distances, tf.float32)  # 转换为浮点数

    def build_optim(self):
        # Update moving_mean and moving_variance for batch normalization layers
        update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS)  # 获取批处理标准化层的更新操作
        with tf.control_dependencies(update_ops):
            with tf.name_scope('reinforce'):
                # Actor learning rate
                self.lr1 = tf.train.exponential_decay(self.lr1_start, self.global_step, self.lr1_decay_step,
                                                      self.lr1_decay_rate, staircase=False, name="learning_rate1")  # 指数衰减学习率
                # Optimizer
                self.opt1 = tf.train.AdamOptimizer(learning_rate=self.lr1, beta1=0.9, beta2=0.99, epsilon=0.0000001)  # Adam优化器
                # Discounted reward
                self.reward_baseline = tf.stop_gradient(self.reward - self.critic.predictions)  # [Batch size, 1]
                # Loss
                self.loss1 = tf.reduce_mean(self.reward_baseline * self.log_softmax, 0)  # 损失函数
                # Minimize step
                gvs = self.opt1.compute_gradients(self.loss1)  # 计算梯度
                capped_gvs = [(tf.clip_by_norm(grad, 1.), var) for grad, var in gvs if grad is not None]  # L2裁剪
                self.train_step1 = self.opt1.apply_gradients(capped_gvs, global_step=self.global_step)  # 应用梯度更新全局步数

            with tf.name_scope('state_value'):
                # Critic learning rate
                self.lr2 = tf.train.exponential_decay(self.lr2_start, self.global_step2, self.lr2_decay_step,
                                                      self.lr2_decay_rate, staircase=False, name="learning_rate1")  # 指数衰减学习率
                # Optimizer
                self.opt2 = tf.train.AdamOptimizer(learning_rate=self.lr2, beta1=0.9, beta2=0.99, epsilon=0.0000001)  # Adam优化器
                # Loss
                self.loss2 = tf.losses.mean_squared_error(self.reward, self.critic.predictions, weights=1.0)  # 均方误差损失
                # Minimize step
                gvs2 = self.opt2.compute_gradients(self.loss2)  # 计算梯度
                capped_gvs2 = [(tf.clip_by_norm(grad, 1.), var) for grad, var in gvs2 if grad is not None]  # L2裁剪
                self.train_step2 = self.opt2.apply_gradients(capped_gvs2, global_step=self.global_step2)  # 应用梯度更新全局步数
