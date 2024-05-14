import math
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

class Transformer_encoder_net(nn.Module):
    """
    Encoder network based on self-attention transformer
    Inputs :  
      h of size      (bsz, nb_nodes+1, dim_emb)    batch of input cities
    Outputs :  
      h of size      (bsz, nb_nodes+1, dim_emb)    batch of encoded cities
      score of size  (bsz, nb_nodes+1, nb_nodes+1) batch of attention scores
    """
    def __init__(self, dim_emb, nb_layers=6, nb_heads=8, dim_ff=512, batchnorm=True):
        super(Transformer_encoder_net, self).__init__()
        assert dim_emb == nb_heads* (dim_emb//nb_heads) # check if dim_emb is divisible by nb_heads
        self.MHA_layers = nn.ModuleList( [nn.MultiheadAttention(dim_emb, nb_heads) for _ in range(nb_layers)] )
        self.linear1_layers = nn.ModuleList( [nn.Linear(dim_emb, dim_ff) for _ in range(nb_layers)] )
        self.linear2_layers = nn.ModuleList( [nn.Linear(dim_ff, dim_emb) for _ in range(nb_layers)] )   
        if batchnorm:
            self.norm1_layers = nn.ModuleList( [nn.BatchNorm1d(dim_emb) for _ in range(nb_layers)] )
            self.norm2_layers = nn.ModuleList( [nn.BatchNorm1d(dim_emb) for _ in range(nb_layers)] )
        else:
            self.norm1_layers = nn.ModuleList( [nn.LayerNorm(dim_emb) for _ in range(nb_layers)] )
            self.norm2_layers = nn.ModuleList( [nn.LayerNorm(dim_emb) for _ in range(nb_layers)] )
        self.nb_layers = nb_layers
        self.nb_heads = nb_heads
        self.batchnorm = batchnorm
        
    def forward(self, h):      
        # PyTorch nn.MultiheadAttention requires input size (seq_len, bsz, dim_emb) 
        h = h.transpose(0,1) # size(h)=(nb_nodes, bsz, dim_emb)
        # L layers
        for i in range(self.nb_layers):
            h_rc = h # residual connection, size(h_rc)=(nb_nodes, bsz, dim_emb)
            h, score = self.MHA_layers[i](h, h, h) # size(h)=(nb_nodes, bsz, dim_emb), size(score)=(bsz, nb_nodes, nb_nodes)
            # add residual connection
            h = h_rc + h # size(h)=(nb_nodes, bsz, dim_emb)
            if self.batchnorm:
                # Pytorch nn.BatchNorm1d requires input size (bsz, dim, seq_len)
                h = h.permute(1,2,0).contiguous() # size(h)=(bsz, dim_emb, nb_nodes)
                h = self.norm1_layers[i](h)       # size(h)=(bsz, dim_emb, nb_nodes)
                h = h.permute(2,0,1).contiguous() # size(h)=(nb_nodes, bsz, dim_emb)
            else:
                h = self.norm1_layers[i](h)       # size(h)=(nb_nodes, bsz, dim_emb)
            # feedforward
            h_rc = h # residual connection
            h = self.linear2_layers[i](torch.relu(self.linear1_layers[i](h)))
            h = h_rc + h # size(h)=(nb_nodes, bsz, dim_emb)
            if self.batchnorm:
                h = h.permute(1,2,0).contiguous() # size(h)=(bsz, dim_emb, nb_nodes)
                h = self.norm2_layers[i](h)       # size(h)=(bsz, dim_emb, nb_nodes)
                h = h.permute(2,0,1).contiguous() # size(h)=(nb_nodes, bsz, dim_emb)
            else:
                h = self.norm2_layers[i](h) # size(h)=(nb_nodes, bsz, dim_emb)
        # Transpose h
        h = h.transpose(0, 1) # size(h)=(bsz, nb_nodes, dim_emb)
        return h, score

class Encoder(nn.Module):
    """将静态和动态状态使用一维卷积进行编码"""

    def __init__(self, input_size, hidden_size):
        super(Encoder, self).__init__()
        self.conv = nn.Conv1d(input_size, hidden_size, kernel_size=1)
        self.transfomer = Transformer_encoder_net(hidden_size)

    def forward(self, input):
        output = self.conv(input).permute(0, 2, 1)
        output, _ = self.transfomer(output)
        return output.permute(0, 2, 1)  # (batch, hidden_size, seq_len)
    
# class Encoder(nn.Module):
#     """将静态和动态状态使用一维卷积进行编码"""

#     def __init__(self, input_size, hidden_size):
#         super(Encoder, self).__init__()
#         self.conv = nn.Conv1d(input_size, hidden_size, kernel_size=1)

#     def forward(self, input):
#         output = self.conv(input)
#         return output  # (batch, hidden_size, seq_len)


class Attention(nn.Module):
    """计算当前状态下输入节点的注意力"""

    # def __init__(self, hidden_size, sequence_size):
    def __init__(self, hidden_size):
        super(Attention, self).__init__()

        # W矩阵处理来自静态解码器元素的特征
        
        # self.v = nn.Parameter(torch.empty((sequence_size, hidden_size)))
        self.v = nn.Parameter(torch.empty((1, hidden_size)))

        self.W = nn.Parameter(torch.empty((hidden_size, 3 * hidden_size)))

        nn.init.xavier_uniform_(self.v)
        nn.init.xavier_uniform_(self.W)

    def forward(self, static_hidden, dynamic_hidden, decoder_hidden):

        batch_size = static_hidden.size(0)
        sequence_size = static_hidden.size(2)

        hidden = decoder_hidden.unsqueeze(2).expand_as(static_hidden)
        hidden = torch.cat((static_hidden, dynamic_hidden, hidden), dim=1)

        # 拓展维度用于进行批量矩阵相乘。
        W = self.W.expand(batch_size, -1, -1)
        # v = self.v.expand(batch_size, -1, -1)
        v = self.v.expand(batch_size, sequence_size, -1)

        attns = torch.bmm(v, torch.tanh(torch.bmm(W, hidden)))
        # attns = F.softmax(attns, dim=2)  # (batch, seq_len)
        attns = F.softmax(attns.view(attns.size(0), -1), dim=1).view(attns.size(0), attns.size(1), -1)

        return attns


class Pointer(nn.Module):
    """给定前一个状态和输入的embedding层，计算下一个状态"""

    # def __init__(self, hidden_size, sequence_size, areas, num_layers=1, dropout=0.2):
    def __init__(self, hidden_size, areas, num_layers=1, dropout=0.2):
        super(Pointer, self).__init__()

        self.hidden_size = hidden_size
        self.num_layers = num_layers

        # 用于计算选择下一个状态的概率
        self.v = nn.Parameter(torch.empty((areas, hidden_size)))

        self.W = nn.Parameter(torch.empty((hidden_size, 2 * hidden_size)))

        nn.init.xavier_uniform_(self.v)
        nn.init.xavier_uniform_(self.W)
        # nn.init.constant_(self.bias, 0.)

        # 用于计算当前解码器输出的表征
        self.gru = nn.GRU(hidden_size, hidden_size, num_layers,
                          batch_first=True,
                          dropout=dropout if num_layers > 1 else 0)
        # self.encoder_attn = Attention(hidden_size, sequence_size)
        self.encoder_attn = Attention(hidden_size)

        self.drop_rnn = nn.Dropout(p=dropout)
        self.drop_hh = nn.Dropout(p=dropout)

    def forward(self, static_hidden, dynamic_hidden, decoder_hidden, last_hh):

        rnn_out, last_hh = self.gru(decoder_hidden.transpose(2, 1), last_hh)
        rnn_out = rnn_out.squeeze(1)

        # 始终在RNN输出上使用dropout
        rnn_out = self.drop_rnn(rnn_out)
        if self.num_layers == 1:
            # 多层时dropout已启用
            last_hh = self.drop_hh(last_hh)

        # 给定输出的总结，找到输入的上下文
        enc_attn = self.encoder_attn(static_hidden, dynamic_hidden, rnn_out)
        context = enc_attn.bmm(static_hidden.permute(0, 2, 1))  # (B, 1, num_feats)
        # 使用批量矩阵相乘操作计算下一个输出
        # context = context.transpose(1, 2).expand_as(static_hidden)
        context = context.transpose(1, 2)
        energy = torch.cat((static_hidden, context), dim=1)  # (B, num_feats, seq_len)

        W = self.W.expand(energy.size(0), -1, -1)
        v = self.v.expand(energy.size(0), -1, -1)

        probs = torch.bmm(v, torch.tanh(torch.bmm(W, energy)))
    
        return probs, last_hh

class DRL4TSP(nn.Module):
    """定义主要的编码器、解码器和指针网络组合模型

    参数说明
    ----------
    static_size: 整型
       定义模型的静态元素中特征数量
        (e.g. 采用二维坐标(x, y)该参数为 2)
    dynamic_size: 整型(> 1)
        定义模型中动态元素的特征数量
        (e.g. 只有一个需求属性的vrp问题动态元素定义为(load, demand), 该参数为 2)
    hidden_size: 整型
        定义静态、动态和解码器输出单元的隐藏层单元数量
    update_fn: 可为空的函数
        若不为空，则该函数将用于输入中动态元素的更新，并在每次决策出新的点后调用。
    mask_fn: 可为空的函数
        允许我们指定哪些输入序列元素可以被选择
        用于加快网络的训练速度，本质上是本算法一个“补丁
        若不提供掩码，则算法将在固定的迭代次数后终止搜索，以避免路径无限延伸
    num_layers: 整型
        指定在解码器RNN中使用的隐藏层数量
    dropout: 浮点型
        定义解码器衰减率
    """

    # def __init__(self, static_size, dynamic_size, hidden_size, sequence_size, areas, max_load=1e7,
    #              num_layers=1, dropout=0.1, update_fn=None, mask_fn=None, ):
    def __init__(self, static_size, dynamic_size, hidden_size, areas, max_load=1.5e3,
                 num_layers=1, dropout=0.1, update_fn=None, mask_fn=None, ):
        super(DRL4TSP, self).__init__()

        if dynamic_size < 1:
            raise ValueError(':param dynamic_size: must be > 0, even if the '
                             'problem has no dynamic elements')
        self.max_load = max_load
        self.areas = areas

        self.update_fn = update_fn
        self.mask_fn = mask_fn

        # 定义编码器、解码器及指针网络
        self.static_encoder = Encoder(static_size, hidden_size)
        self.dynamic_encoder = Encoder(dynamic_size, hidden_size)
        self.decoder = Encoder(static_size, hidden_size)
        # self.pointer = Pointer(hidden_size, sequence_size, areas, num_layers, dropout)
        self.pointer = Pointer(hidden_size, areas, num_layers, dropout)

        for p in self.parameters():
            if len(p.shape) > 1:
                nn.init.xavier_uniform_(p)

        # 当解码器初始状态未指定时，作为替补初始状态使用。
        self.x0 = torch.zeros((1, static_size, 1), requires_grad=True, device=device)

    def forward(self, static, dynamic, decoder_input=None, last_hh=None, ere=1):
        """
        参数说明
        ----------
        static: (batch_size, feats, num_cities)
            静态元素
        dynamic: Array of size (batch_size, feats, num_cities)
            动态元素
            对于VRP问题，这些元素可以是每个城市的负载和需求
        decoder_input: (batch_size, num_feats)
            解码器的输入
            我们仅使用静态元素（如（x，y）坐标），理论上也可以选择其他合理的参数。
        last_hh: Array of size (batch_size, num_hidden)
            RNN最后输出的隐含状态
        """

        batch_size, input_size, sequence_size = static.size()

        if decoder_input is None:
            decoder_input = self.x0.expand(batch_size, -1, -1)

        # 启用掩码，若未提供，则不进行更新。
        dmd = dynamic[:, 1]
        tmp = 0.5 * static[:, 2] + 0.3
        dmd = (float(self.max_load) * dmd) / (ere * (1 + tmp) ** 2)
        dmd = dmd.round().unsqueeze(1).expand(-1, self.areas, -1)
        stda = torch.arange(self.areas).expand(batch_size, sequence_size, -1).permute(0, 2, 1).to(device)
        mask = torch.gt(dmd, stda).detach()
        mask[:, :, 0] = False

        # 保存输出结点序列的相关数据
        tour_idx, tour_logp = [], []
        max_steps = sequence_size #if self.mask_fn is None else 1000

        # 静态元素只需提取一次特征，并可在迭代过程中重复使用
        # 动态元素则在每次输出一个结点后发生变化，需要重新计算
        static_hidden = self.static_encoder(static)
        dynamic_hidden = self.dynamic_encoder(dynamic)

        for _ in range(max_steps):

            if not mask.byte().any():
                break

            # 为每个添加到序列中的元素计算隐含矩阵
            decoder_hidden = self.decoder(decoder_input)

            probs, last_hh = self.pointer(static_hidden,
                                          dynamic_hidden,
                                          decoder_hidden, last_hh)

            probs = F.softmax((probs + mask.float().log()).reshape(batch_size, -1), dim=1)
            # 训练模式下，利用该步概率抽样
            # 测试模式下，选取该步概率最大的点
            if self.training:
                m = torch.distributions.Categorical(probs)
                smp = m.sample()
                while not torch.gather(mask.view(batch_size, -1), 1, smp.unsqueeze(1)).byte().all():
                    smp = m.sample()
                logp = m.log_prob(smp)
            else:
                prob, smp = torch.max(probs, 1)  # Greedy
                logp = prob.log()

            # 得出新节点后更新动态元素表征
            if self.update_fn is not None:
                dynamic = self.update_fn(static, dynamic, smp.data)
                dynamic_hidden = self.dynamic_encoder(dynamic)

                # # 小批次中计算VRP时，某些路径可能有0个途经点
                # # 这种情况下，我们强制车辆停留在起点，并将logp设为0。
                # is_done = dynamic[:, 1].sum(1).eq(0).float()
                # logp = logp * (1. - is_done)

            # 同时更新掩码，避免节点重复访问
            if self.mask_fn is not None:
                mask = self.mask_fn(mask, dynamic, smp.data).detach()

            tour_logp.append(logp.unsqueeze(1))
            tour_idx.append(smp.data.unsqueeze(1))

            decoder_input = torch.gather(static, 2,
                                         (smp % sequence_size).view(-1, 1, 1)
                                         .expand(-1, input_size, 1)).detach()

        tour_idx = torch.cat(tour_idx, dim=1)  # (batch_size, seq_len)
        tour_logp = torch.cat(tour_logp, dim=1)  # (batch_size, seq_len)

        return tour_idx, tour_logp


if __name__ == '__main__':
    raise Exception('Cannot be called from main')