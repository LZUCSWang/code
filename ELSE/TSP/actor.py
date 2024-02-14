import torch
import torch.nn as nn
import torch.nn.functional as F

from config import Config, load_pkl, pkl_parser
from env import Env_tsp


class Greedy(nn.Module):
    def __init__(self):
        super().__init__()

    def forward(self, log_p):
        return torch.argmax(log_p, dim=1).long()


class Categorical(nn.Module):
    def __init__(self):
        super().__init__()

    def forward(self, log_p):
        return torch.multinomial(log_p.exp(), 1).long().squeeze(1)

# https://github.com/higgsfield/np-hard-deep-reinforcement-learning/blob/master/Neural%20Combinatorial%20Optimization.ipynb


class PtrNet1(nn.Module):
    def __init__(self, cfg):
        # 定义了一个名为__init__的构造函数，该函数用于初始化类的实例。它接受一个cfg参数，用于配置模型的超参数。
        super().__init__()
  # 调用父类nn.Module的构造函数，以确保正确初始化神经网络模型。
        self.Embedding = nn.Linear(2, cfg.embed, bias=False)
        # 定义了一个名为Embedding的线性层，该层将输入的2维坐标转换为embed维的向量。cfg.embed参数指定了嵌入空间的维度。bias=False表示不使用偏置项。
        self.Encoder = nn.LSTM(input_size=cfg.embed,
                               hidden_size=cfg.hidden, batch_first=True)
        # 定义了一个名为Encoder的LSTM层，该层将输入的嵌入向量转换为隐藏状态向量。cfg.hidden参数指定了隐藏状态向量的维度。batch_first=True表示输入的第一个维度是batch size。
        self.Decoder = nn.LSTM(input_size=cfg.embed,
                               hidden_size=cfg.hidden, batch_first=True)
        # 定义了一个名为Decoder的LSTM层，该层将输入的嵌入向量转换为隐藏状态向量。cfg.hidden参数指定了隐藏状态向量的维度。batch_first=True表示输入的第一个维度是batch size。
        if torch.cuda.is_available():
            self.Vec = nn.Parameter(torch.cuda.FloatTensor(cfg.embed))
            # 定义了一个名为Vec的可学习参数，该参数是一个1维向量，其长度为cfg.embed。该向量用于计算注意力分布。
            self.Vec2 = nn.Parameter(torch.cuda.FloatTensor(cfg.embed))
            # 定义了一个名为Vec2的可学习参数，该参数是一个1维向量，其长度为cfg.embed。该向量用于计算注意力分布。
        else:
            self.Vec = nn.Parameter(torch.FloatTensor(cfg.embed))
            self.Vec2 = nn.Parameter(torch.FloatTensor(cfg.embed))
        self.W_q = nn.Linear(cfg.hidden, cfg.hidden, bias=True)
        # 定义了一个名为W_q的线性层，该层将隐藏状态向量转换为注意力分布。cfg.hidden参数指定了隐藏状态向量的维度。bias=True表示使用偏置项。
        self.W_ref = nn.Conv1d(cfg.hidden, cfg.hidden, 1, 1)
        # 定义了一个名为W_ref的卷积层，该层将隐藏状态向量转换为注意力分布。cfg.hidden参数指定了隐藏状态向量的维度。
        self.W_q2 = nn.Linear(cfg.hidden, cfg.hidden, bias=True)
        # 定义了一个名为W_q2的线性层，该层将隐藏状态向量转换为注意力分布。cfg.hidden参数指定了隐藏状态向量的维度。bias=True表示使用偏置项。
        self.W_ref2 = nn.Conv1d(cfg.hidden, cfg.hidden, 1, 1)
        # 定义了一个名为W_ref2的卷积层，该层将隐藏状态向量转换为注意力分布。cfg.hidden参数指定了隐藏状态向量的维度。
        self.dec_input = nn.Parameter(torch.FloatTensor(cfg.embed))
        # 定义了一个名为dec_input的可学习参数，该参数是一个1维向量，其长度为cfg.embed。该向量用于初始化解码器的输入。
        self._initialize_weights(cfg.init_min, cfg.init_max)
        # 调用_initialize_weights函数，以确保正确初始化神经网络模型。
        self.clip_logits = cfg.clip_logits
        # 定义了一个名为clip_logits的参数，该参数用于控制解码器输出的范围。
        self.softmax_T = cfg.softmax_T
        # 定义了一个名为softmax_T的参数，该参数用于控制softmax函数的温度。
        self.n_glimpse = cfg.n_glimpse
        # 定义了一个名为n_glimpse的参数，该参数用于控制注意力机制的迭代次数。
        self.city_selecter = {'greedy': Greedy(), 'sampling': Categorical()}.get(
            cfg.decode_type, None)
        # 定义了一个名为city_selecter的参数，该参数用于控制解码器的解码策略。cfg.decode_type参数指定了解码策略。

    def _initialize_weights(self, init_min=-0.08, init_max=0.08):
        for param in self.parameters():
            # 遍历神经网络模型的所有参数。
            nn.init.uniform_(param.data, init_min, init_max)
            # 为每个参数赋予随机的初始值。

    def forward(self, x, device):
        '''	x: (batch, city_t, 2)
                enc_h: (batch, city_t, embed)
                dec_input: (batch, 1, embed)
                h: (1, batch, embed)
                return: pi: (batch, city_t), ll: (batch)
        '''
        x = x.to(device)
        # 将输入的坐标转换为指定的设备。
        batch, city_t, _ = x.size()
        # 获取输入的batch size和城市数量。
        embed_enc_inputs = self.Embedding(x)
        # 将输入的坐标转换为嵌入向量。
        embed = embed_enc_inputs.size(2)
        # 获取嵌入向量的维度。
        mask = torch.zeros((batch, city_t), device=device)
        # 定义了一个名为mask的张量，该张量用于控制解码器的解码过程。
        enc_h, (h, c) = self.Encoder(embed_enc_inputs, None)
        # 将嵌入向量转换为隐藏状态向量。
        ref = enc_h
        # 将隐藏状态向量作为注意力分布的参考。
        pi_list, log_ps = [], []
        # 定义了两个列表，用于存储解码器的输出。
        dec_input = self.dec_input.unsqueeze(
            0).repeat(batch, 1).unsqueeze(1).to(device)
        # 将解码器的输入初始化为dec_input。
        for i in range(city_t):
            # 遍历城市数量。
            _, (h, c) = self.Decoder(dec_input, (h, c))
            # 将解码器的输入转换为隐藏状态向量。
            query = h.squeeze(0)
            # 获取隐藏状态向量。
            for i in range(self.n_glimpse):
                # 遍历注意力机制的迭代次数。
                query = self.glimpse(query, ref, mask)
                # 使用注意力机制获取下一个城市。
            logits = self.pointer(query, ref, mask)
            # 使用注意力机制获取下一个城市。
            log_p = torch.log_softmax(logits, dim=-1)
            # 将注意力分布转换为概率分布。
            next_node = self.city_selecter(log_p)
            # 使用解码策略获取下一个城市。
            dec_input = torch.gather(
                input=embed_enc_inputs, dim=1, index=next_node.unsqueeze(-1).unsqueeze(-1).repeat(1, 1, embed))
            # 将下一个城市的嵌入向量作为解码器的输入。
            pi_list.append(next_node)
            # 将下一个城市添加到pi_list列表中。
            log_ps.append(log_p)
            # 将下一个城市的概率分布添加到log_ps列表中。
            mask += torch.zeros((batch, city_t), device=device).scatter_(dim=1,
                                                                         index=next_node.unsqueeze(1), value=1)
            # 更新mask张量，防止重复访问城市。
        pi = torch.stack(pi_list, dim=1)
        # 将pi_list列表转换为张量。
        ll = self.get_log_likelihood(torch.stack(log_ps, 1), pi)
        # 计算解码器的输出的对数似然。
        return pi, ll

    def glimpse(self, query, ref, mask, inf=1e8):
        """	-ref about torch.bmm, torch.matmul and so on
                https://qiita.com/tand826/items/9e1b6a4de785097fe6a5
                https://qiita.com/shinochin/items/aa420e50d847453cc296

                        Args: 
                query: the hidden state of the decoder at the current
                (batch, 128)
                ref: the set of hidden states from the encoder. 
                (batch, city_t, 128)
                mask: model only points at cities that have yet to be visited, so prevent them from being reselected
                (batch, city_t)
        """
        u1 = self.W_q(query).unsqueeze(-1).repeat(1, 1,
                                                  ref.size(1))  # u1: (batch, 128, city_t)
        u2 = self.W_ref(ref.permute(0, 2, 1))  # u2: (batch, 128, city_t)
        V = self.Vec.unsqueeze(0).unsqueeze(0).repeat(ref.size(0), 1, 1)
        u = torch.bmm(V, torch.tanh(u1 + u2)).squeeze(1)
        # V: (batch, 1, 128) * u1+u2: (batch, 128, city_t) => u: (batch, 1, city_t) => (batch, city_t)
        u = u - inf * mask
        a = F.softmax(u / self.softmax_T, dim=1)
        d = torch.bmm(u2, a.unsqueeze(2)).squeeze(2)
        # u2: (batch, 128, city_t) * a: (batch, city_t, 1) => d: (batch, 128)
        return d

    def pointer(self, query, ref, mask, inf=1e8):
        """	Args: 
                query: the hidden state of the decoder at the current
                (batch, 128)
                ref: the set of hidden states from the encoder. 
                (batch, city_t, 128)
                mask: model only points at cities that have yet to be visited, so prevent them from being reselected
                (batch, city_t)
        """
        u1 = self.W_q2(query).unsqueeze(-1).repeat(1, 1,
                                                   ref.size(1))  # u1: (batch, 128, city_t)
        # 使用权重矩阵 W_q2 对 query 进行线性变换，然后扩展维度并重复城市数量次
        # u1: (batch, 128, city_t)
        u2 = self.W_ref2(ref.permute(0, 2, 1))  # u2: (batch, 128, city_t)
        # 使用权重矩阵 W_ref2 对 ref 进行线性变换，同时进行维度转置
        V = self.Vec2.unsqueeze(0).unsqueeze(0).repeat(ref.size(0), 1, 1)
        # 创建一个张量 V，用于加权和
        u = torch.bmm(V, self.clip_logits * torch.tanh(u1 + u2)).squeeze(1)
        # 计算点积注意力：通过乘以 clip_logits 和双曲正切函数处理的 u1+u2，然后与 V 进行批量矩阵乘法
        # V: (batch, 1, 128) * u1+u2: (batch, 128, city_t) => u: (batch, 1, city_t) => (batch, city_t)
        # 将 u 减去一个非常大的值，以便在应用遮罩时限制选择
        u = u - inf * mask
        return u

    def get_log_likelihood(self, _log_p, pi):
        """
                Args:
                        _log_p: 概率对数矩阵，表示从一个城市到另一个城市的概率。
                        形状为 (batch, city_t, city_t)

                        pi: 预测的旅行路径，表示访问城市的顺序。
                        形状为 (batch, city_t)

                Returns:
                        一个包含批次中每个样本的对数似然的张量。
                        形状为 (batch)
                """
        # 使用 torch.gather 从 _log_p 中收集预测路径 pi 的概率对数
        log_p = torch.gather(input=_log_p, dim=2, index=pi[:, :, None])

        # 压缩最后一个维度，将形状变为 (batch, city_t)
        log_p = log_p.squeeze(-1)

        # 对每个样本中的对数似然求和，得到一个包含每个样本似然的张量
        return torch.sum(log_p, 1)


if __name__ == '__main__':
    cfg = load_pkl(pkl_parser().path)
    model = PtrNet1(cfg)
    inputs = torch.randn(3, 20, 2)
    pi, ll = model(inputs, device='cpu')
    print('pi:', pi.size(), pi)
    print('log_likelihood:', ll.size(), ll)

    cnt = 0
    for i, k in model.state_dict().items():
        print(i, k.size(), torch.numel(k))
        cnt += torch.numel(k)
    print('total parameters:', cnt)

    # ll.mean().backward()
    # print(model.W_q.weight.grad)

    cfg.batch = 3
    env = Env_tsp(cfg)
    cost = env.stack_l(inputs, pi)
    print('cost:', cost.size(), cost)
    cost = env.stack_l_fast(inputs, pi)
    print('cost:', cost.size(), cost)
