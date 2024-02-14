import tensorflow as tf
from tensorflow.contrib.rnn import LSTMCell

class Critic(object):
    def __init__(self, config):
        self.config = config

        # Data config
        self.batch_size = config.batch_size  # 批处理大小
        self.max_length = config.max_length  # 输入序列长度（城市数量）
        self.input_dimension = config.input_dimension  # 城市维度（坐标）

        # Network config
        self.input_embed = config.input_embed  # 嵌入空间维度
        self.num_neurons = config.hidden_dim  # 隐藏状态维度（LSTM单元）
        self.initializer = tf.contrib.layers.xavier_initializer()  # 变量初始化器

        # Baseline setup
        self.init_baseline = self.max_length / 2.  # 基线初始值（城市数量的一半）

        # Training config
        self.is_training = config.training_mode  # 是否处于训练模式

    def predict_rewards(self, input_):
        with tf.variable_scope("encoder"):
            with tf.variable_scope("embedding"):
                # Embed input sequence
                W_embed = tf.get_variable("weights", [1, self.input_dimension, self.input_embed],
                                          initializer=self.initializer)  # 获取嵌入权重
                embedded_input = tf.nn.conv1d(input_, W_embed, 1, "VALID", name="embedded_input")  # 卷积嵌入
                # Batch Normalization
                embedded_input = tf.layers.batch_normalization(embedded_input, axis=2, training=self.is_training,
                                                               name='layer_norm', reuse=None)  # 批处理标准化

            with tf.variable_scope("dynamic_rnn"):
                # Encode input sequence
                cell1 = LSTMCell(self.num_neurons, initializer=self.initializer)  # 创建LSTM单元
                # Return the output activations and last hidden state (c,h) as tensors.
                encoder_output, encoder_state = tf.nn.dynamic_rnn(cell1, embedded_input, dtype=tf.float32)  # 动态RNN编码
                frame = encoder_state[0]  # 获取LSTM的最后一个隐藏状态

            # Glimpse
            with tf.variable_scope("glimpse"):
                self.W_ref_g = tf.get_variable("W_ref_g", [1, self.num_neurons, self.num_neurons],
                                               initializer=self.initializer)  # 获取权重
                self.W_q_g = tf.get_variable("W_q_g", [self.num_neurons, self.num_neurons],
                                             initializer=self.initializer)  # 获取权重
                self.v_g = tf.get_variable("v_g", [self.num_neurons], initializer=self.initializer)  # 获取权重

                # Attending mechanism
                encoded_ref_g = tf.nn.conv1d(encoder_output, self.W_ref_g, 1, "VALID",
                                             name="encoded_ref_g")  # 卷积编码的参考向量
                encoded_query_g = tf.expand_dims(tf.matmul(frame, self.W_q_g, name="encoded_query_g"),
                                                 1)  # 编码的查询向量
                scores_g = tf.reduce_sum(self.v_g * tf.tanh(encoded_ref_g + encoded_query_g), [-1],
                                         name="scores_g")  # 分数计算
                attention_g = tf.nn.softmax(scores_g, name="attention_g")  # 注意力分布

                # 1 glimpse = Linear combination of reference vectors (defines new query vector)
                glimpse = tf.multiply(encoder_output, tf.expand_dims(attention_g, 2))  # 获取瞥视（新的查询向量）
                glimpse = tf.reduce_sum(glimpse, 1)

            with tf.variable_scope("ffn"):
                # ffn 1
                h0 = tf.layers.dense(glimpse, self.num_neurons, activation=tf.nn.relu,
                                     kernel_initializer=self.initializer)  # 全连接层
                # ffn 2
                w1 = tf.get_variable("w1", [self.num_neurons, 1], initializer=self.initializer)  # 获取权重
                b1 = tf.Variable(self.init_baseline, name="b1")  # 创建基线变量
                self.predictions = tf.squeeze(tf.matmul(h0, w1) + b1)  # 预测奖励值
