"""VRP的主要任务是解决以下问题：

每个城市都有一个需求量（范围在1到9之间），必须由车辆提供服务
每辆车都有一个容量限制（根据问题而定），必须访问所有城市
当车辆的负载为0时，它必须返回到配送中心进行补给
"""

import os
import numpy as np
import torch
from torch.utils.data import Dataset
from torch.autograd import Variable
import matplotlib

matplotlib.use('Agg')
import matplotlib.pyplot as plt
# import torch.nn.functional as F

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

class VehicleRoutingDataset(Dataset):
    def __init__(self, num_samples, input_size, max_load=1.5e3, max_demand=20,
                 eap=2, ere=1, seed=None):
        super(VehicleRoutingDataset, self).__init__()

        # if max_load < max_demand:
        #     raise ValueError(':param max_load: must be > max_demand')

        if seed is None:
            seed = np.random.randint(1234567890)
        np.random.seed(seed)
        torch.manual_seed(seed)

        self.eap = eap
        self.ere = ere

        self.num_samples = num_samples
        self.max_load = max_load
        self.max_demand = max_demand

        # 每个路径中起点固定
        locations = torch.rand((num_samples, 2, input_size))
        degradations = torch.randint(3, 9, (num_samples, 1, input_size)) / float(10.) #定义退化程度
        # locations[:, 2, 0] = 0 # 起点退化程度为0

        self.static = torch.tensor(np.concatenate((locations, 2 * (degradations - 0.3)), axis=1)).detach()
        self.static[:, 2, 0] = 0

        # 所有状态都将扩展当前负载
        # 将输入放缩至[0, 1]内以统一量纲
        dynamic_shape = (num_samples, 1, input_size)
        loads = torch.full(dynamic_shape, 1.)

        # 将任何状态的需求（在[1, max_demand)范围内）按最大负载进行缩放
        # 例如，如果负载为10，最大需求为30，则需求将缩放到(0, 3)范围内
        demands = torch.randint(5, max_demand + 1, dynamic_shape)
        self.areas = demands.data
        demands = (ere * demands * (1 + degradations) ** 2) / float(max_load)

        demands[:, 0, 0] = 0  # 起点需求为0
        self.dynamic = torch.tensor(np.concatenate((loads, demands), axis=1)).detach()

    def __len__(self):
        return self.num_samples

    def __getitem__(self, idx):
        # (static, dynamic, start_loc)
        return (self.static[idx], self.dynamic[idx], self.areas[idx].squeeze(), self.static[idx, :, 0:1])

    def update_mask(self, mask, dynamic, chosen_idx=None):
        """一个节点仅允许访问一次
        """
        chosen_idx = chosen_idx % dynamic.size(2)
        mask[torch.arange(mask.size(0)).unsqueeze(1), :, chosen_idx.unsqueeze(1)] = 0
        # mask.scatter_(1, chosen_idx.unsqueeze(1), 0)
        return mask

    def update_dynamic(self, static, dynamic, chosen_idx):
        """更新动态元素(load, demand)"""

        # 根据我们访问结点的不同情况，以不同的方式更新动态元素
        visit = chosen_idx.ne(0)
        # depot = chosen_idx.eq(0)

        ptr = chosen_idx.data % dynamic.size(2)
        area = chosen_idx.data // dynamic.size(2) + 1

        # 复制动态变量，防止混淆初始图
        all_loads = dynamic[:, 0].clone()
        all_demands = dynamic[:, 1].clone()
        all_degras = 0.5 * static[:, 2].clone() + 0.3

        load = torch.gather(all_loads, 1, ptr.unsqueeze(1))
        demand = torch.gather(all_demands, 1, ptr.unsqueeze(1))
        degra = torch.gather(all_degras, 1, ptr.unsqueeze(1))

        restore = ((self.ere * area.unsqueeze(1) * (1 + degra) ** 2) + self.eap * area.unsqueeze(1)) / float(self.max_load)

        # 在整个小批量数据中选择访问一个结点
        if visit.any():

            new_load = torch.clamp(torch.floor(load - restore), min=0)
            new_demand = torch.clamp(torch.floor(demand - restore), min=0)

            # 将负载广播到所有节点，但单独更新需求
            visit_idx = ptr.nonzero().squeeze()

            all_loads[visit_idx] = new_load[visit_idx]
            # all_demands[visit_idx, ptr[visit_idx]] = 0
            all_demands[visit_idx, ptr[visit_idx]] = new_demand[visit_idx].view(-1)
            # all_demands[visit_idx, 0] = -1. + new_load[visit_idx].view(-1)

        # 返回起点以填充负载
        # if depot.any():
        #     all_loads[depot.nonzero().squeeze()] = 1.
        #     all_demands[depot.nonzero().squeeze(), 0] = 0.

        tensor = torch.cat((all_loads.unsqueeze(1), all_demands.unsqueeze(1)), 1)
        return torch.tensor(tensor.data, device=dynamic.device)


def reward(static, areas, tour_indices, max_load=1.5e3, land_size=7, eap=2, ere=1):
    """
    给定规划的路径，计算所有节点之间的欧氏距离
    """

    ptr = tour_indices.detach() % static.size(2)
    area = 1 + tour_indices.detach() // static.size(2)

    # 将路径格式进行转换
    idx = ptr.unsqueeze(1).expand(-1, static.size(1), -1)
    tour = torch.gather(static.detach(), 2, idx).permute(0, 2, 1)

    # 确保我们始终返回到起点
    start = static.detach()[:, :, 0].unsqueeze(1)
    end = torch.tensor([0.5, 0.5, 0]).expand(start.size(0), 1, -1).to(device)
    # end = static.data[:, :, 0].unsqueeze(1)
    y = torch.cat((start, tour, end), dim=1)[:, :, 0:2]

    # 连续点之间的距离
    tour_len = torch.sqrt(torch.sum(torch.pow(y[:, :-1] - y[:, 1:], 2), dim=2))

    degras = 0.5 * static.detach()[:, 2].clone() + 0.3
    seed_avg = torch.gather((1 + degras) ** 2, 1, ptr)
    bow_weight = seed_avg * area / 500.
    P = torch.cat((bow_weight, torch.zeros(seed_avg.size(0)).unsqueeze(1).to(device)), dim=1)
    const_w = ((9.8 ** 3) / (2 * 1.024 * 0.2 * 6)) ** 0.5
    P = torch.flip(P, dims=[1])
    P[:, 0] = torch.tensor([1.5]).expand(seed_avg.size(0))
    for i in range(1, P.size(1)):
        P[:, i] += P[:, i - 1]
    P = const_w * P ** 1.5

    path_cost = land_size * (tour_len * torch.flip(P, dims=[1])).sum(1)
    restore_cost = (ere * area * seed_avg).sum(1)
    reserve_cost = (eap * area).sum(1)

    energy_cost = path_cost + reserve_cost + restore_cost
    energy_rest = 1 - energy_cost / max_load
    restore_rate = area.sum(1) / areas.detach()[:, 1:].sum(1)

    # energy_rest = torch.where(energy_rest > 0.0, torch.tensor(1.0).to(device), energy_rest)
    pel = torch.where(energy_rest > 0.0, torch.tensor(10.0).to(device), tour_len.sum(1) * 10)


    # return pel * 1000 * tour_len.sum(1) + (1 - restore_rate) * 10 #3.5/3
    # return pel * 100 * tour_len.sum(1) + area.sum(1) / 50.
    return pel - area.sum(1) / 50.


def render(static, tour_indices, save_path):
    """绘制路径图"""
    tour_indices %= static.size(2)

    plt.close('all')

    num_plots = 3 if int(np.sqrt(len(tour_indices))) >= 3 else 1

    _, axes = plt.subplots(nrows=num_plots, ncols=num_plots,
                           sharex='col', sharey='row')

    if num_plots == 1:
        axes = [[axes]]
    axes = [a for ax in axes for a in ax]

    for i, ax in enumerate(axes):

        # 将序列转化为路径
        idx = tour_indices[i]
        if len(idx.size()) == 1:
            idx = idx.unsqueeze(0)

        idx = idx.expand(static.size(1), -1)

        data = torch.gather(static[i].data, 1, idx)
        end = torch.tensor([0.5]).expand(idx.size(0), -1).to(device)
        data = torch.cat((data, end), dim=1).cpu().numpy()

        ax.plot(data[0], data[1], zorder=1)
        ax.scatter(data[0], data[1], s=4, c='r', zorder=2)
        ax.scatter(data[0, 0], data[1, 0], s=20, c='k', marker='*', zorder=3)

        ax.set_xlim(0, 1)
        ax.set_ylim(0, 1)

    plt.tight_layout()
    plt.savefig(save_path, bbox_inches='tight', dpi=400)