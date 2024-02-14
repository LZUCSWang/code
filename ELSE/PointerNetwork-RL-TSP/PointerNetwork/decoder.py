import tensorflow as tf
from tensorflow.contrib.rnn import LSTMCell
import tensorflow.contrib.distributions as distr

class Pointer_decoder(object):

    def __init__(self, encoder_output, config):
        self.encoder_output = encoder_output  # 编码器的输出，大小为 [Batch大小 x 时间步数 x 隐藏状态维度]
        self.h = tf.transpose(encoder_output, [1, 0, 2])  # 转置编码器输出

        batch_size = encoder_output.get_shape().as_list()[0]  # 批处理大小
        self.seq_length = encoder_output.get_shape().as_list()[1]  # 序列长度
        n_hidden = encoder_output.get_shape().as_list()[2]  # 隐藏状态维度

        self.temperature = config.temperature  
        self.C = config.C  # 对数概率截断
        self.training_mode = config.training_mode  # 训练模式开关

        # 变量初始化器
        initializer = tf.contrib.layers.xavier_initializer()

        # 解码器LSTM单元        
        self.cell = LSTMCell(n_hidden, initializer=initializer)

        # 注意力机制
        with tf.variable_scope("glimpse") as glimpse:
            self.W_ref_g = tf.get_variable("W_ref_g", [1, n_hidden, n_hidden], initializer=initializer)
            self.W_q_g = tf.get_variable("W_q_g", [n_hidden, n_hidden], initializer=initializer)
            self.v_g = tf.get_variable("v_g", [n_hidden], initializer=initializer)

        # 指针机制
        with tf.variable_scope("pointer") as pointer:
            self.W_ref = tf.get_variable("W_ref", [1, n_hidden, n_hidden], initializer=initializer)
            self.W_q = tf.get_variable("W_q", [n_hidden, n_hidden], initializer=initializer)
            self.v = tf.get_variable("v", [n_hidden], initializer=initializer)

        self.log_softmax = []  # 用于存储 log(p_theta(pi(t)|pi(<t),s)) 以进行反向传播
        self.positions = []  # 用于存储任务列表以计算奖励

        # 从起始点（depot）开始
        self.depot_position = tf.constant(self.seq_length - 1, shape=[batch_size])
        self.positions.append(self.depot_position)

        # 跟踪当前城市
        self.current_task = tf.one_hot(self.depot_position, self.seq_length)

        # 跟踪已访问的城市
        self.mask = tf.one_hot(self.depot_position, self.seq_length)

    def loop_decode(self, decoder_initial_state):
        # decoder_initial_state: Tuple Tensor (c,h) of size [batch_size x cell.state_size]
        # decoder_first_input: Tensor [batch_size x cell.state_size]

        # 解码器的初始输入是depot（起始点）
        decoder_first_input = tf.gather(self.h, self.depot_position)[0]

        # 循环解码过程并收集结果
        s, i = decoder_initial_state, decoder_first_input
        for step in range(self.seq_length - 1):
            s, i = self.decode(s, i, step)

        # 返回到起始点（depot）
        self.positions.append(self.depot_position)

        # 堆叠已访问索引
        self.positions = tf.stack(self.positions, axis=1)  # [Batch,seq_length]

        # 在输出步骤上对log_softmax求和
        self.log_softmax = tf.add_n(self.log_softmax)  # [Batch,seq_length-1]

        # 返回堆叠的已访问索引列表和log_softmax以进行反向传播
        return self.positions, self.log_softmax

    # 解码机制的一次传递
    def decode(self, prev_state, prev_input, timestep):
        with tf.variable_scope("loop"):
            if timestep > 0:
                tf.get_variable_scope().reuse_variables()

            # 在先前输入和状态的组合上运行单元
            output, state = self.cell(prev_input, prev_state)

            # 注意力机制
            self.masked_scores = self.attention(self.encoder_output, output)

            # 多项分布
            prob = distr.Categorical(self.masked_scores)

            # 从分布中采样
            position = prob.sample()
            position = tf.cast(position, tf.int32)
            self.positions.append(position)

            # 存储log_prob以供反向传播
            self.log_softmax.append(prob.log_prob(position))

            # 更新当前城市和掩码
            self.current_city = tf.one_hot(position, self.seq_length)
            self.mask = self.mask + self.current_city

            # 获取解码器的新输入
            new_decoder_input = tf.gather(self.h, position)[0]

            return state, new_decoder_input

    # 从查询（解码器输出）和一组参考（编码器输出）中预测下一个解码器输入的分布
    def attention(self, ref, query):

        # 注意力机制
        # ref 编码器输出
        self.encoded_ref_g = tf.nn.conv1d(ref, self.W_ref_g, 1, "VALID",
                                     name="encoded_ref_g")  # [Batch size, seq_length, n_hidden]
        # query 解码器输出
        self.encoded_query_g = tf.expand_dims(tf.matmul(query, self.W_q_g, name="encoded_query_g"),
                                         1)  # [Batch size, 1, n_hidden]
        self.scores_g = tf.reduce_sum(self.v_g * tf.tanh(self.encoded_ref_g + self.encoded_query_g), [-1],
                                 name="scores_g")  # [Batch size, seq_length]

        # 仅考虑当前任务和要应用的任务（应用掩码）
        self.attention_g = tf.nn.softmax(self.scores_g - 100000000. * (self.mask - self.current_task), name="attention_g")
        # 1次瞥视 = 参考向量的线性组合（定义新的查询向量）
        self.glimpse = tf.multiply(ref, tf.expand_dims(self.attention_g, 2))
        self.glimpse = tf.reduce_sum(self.glimpse, 1) + query

        # 使用1次瞥视的指针机制
        self.encoded_ref = tf.nn.conv1d(ref, self.W_ref, 1, "VALID",
                                   name="encoded_ref")  # [Batch size, seq_length, n_hidden]
        self.encoded_query = tf.expand_dims(tf.matmul(self.glimpse, self.W_q, name="encoded_query"),
                                       1)  # [Batch size, 1, n_hidden]
        self.scores = tf.reduce_sum(self.v * tf.tanh(self.encoded_ref + self.encoded_query), [-1],
                               name="scores")  # [Batch size, seq_length]
        if not self.training_mode:
            self.scores1 = self.scores / self.temperature  # 控制采样的多样性（推断模式）
        self.scores1 = self.C * tf.tanh(self.scores)  # 控制熵

        # 只指向要访问的城市（应用掩码）
        masked_scores = self.scores1 - 100000000. * self.mask  # [Batch size, seq_length]

        return masked_scores
