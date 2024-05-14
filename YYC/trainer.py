"""定义组合问题的主训练模型

所需解决的问题必须定义以下函数:
* mask_fn: 掩码函数，可为空
* update_fn: 动态元素更新函数，可为空
* reward_fn: 奖励函数，用于表征解的质量
* render_fn: 绘图函数，绘制一个解的图示，可为空
"""

import os
import csv
import time
import argparse
import datetime
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

import warnings

warnings.filterwarnings("ignore")

from matplotlib import pyplot as plt
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score, silhouette_samples

from torch.utils.data import DataLoader

from model import DRL4TSP, Encoder
from tasks import vrp
from tasks.vrp import VehicleRoutingDataset
from tqdm import tqdm

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
torch.set_printoptions(profile="full")

plt.rcParams["font.sans-serif"] = ["AR PL UKai CN"]  # 用来正常显示中文标签
plt.rcParams["axes.unicode_minus"] = False  # 用来正常显示负号


class StateCritic(nn.Module):
    """估计问题的复杂程度

    基本模块，用于查看编码器+解码器预测的对数概率，返回对问题复杂程度的估计。
    """

    def __init__(self, static_size, dynamic_size, hidden_size):
        super(StateCritic, self).__init__()

        self.static_encoder = nn.Conv1d(static_size, hidden_size, kernel_size=1)
        self.dynamic_encoder = nn.Conv1d(dynamic_size, hidden_size, kernel_size=1)

        self.fc1 = nn.Conv1d(hidden_size * 2, 128, kernel_size=1)
        self.fc2 = nn.Conv1d(128, 20, kernel_size=1)
        self.fc3 = nn.Conv1d(20, 1, kernel_size=1)

        for p in self.parameters():
            if len(p.shape) > 1:
                nn.init.xavier_uniform_(p)

    def forward(self, static, dynamic):

        # 使用访问每个点的概率
        static_hidden = self.static_encoder(static)
        dynamic_hidden = self.dynamic_encoder(dynamic)

        hidden = torch.cat((static_hidden, dynamic_hidden), 1)

        output = F.relu(self.fc1(hidden))
        output = F.relu(self.fc2(output))
        output = self.fc3(output).sum(dim=2)
        return output


def train_plot(ac, cr, re):

    f = open("loss.txt", "w")

    f.write(str(ac) + "\n")
    f.write(str(cr) + "\n")
    f.write(str(re) + "\n")

    plt.rcParams["font.sans-serif"] = ["AR PL UKai CN"]  # 用来正常显示中文标签
    plt.rcParams["axes.unicode_minus"] = False  # 用来正常显示负号

    plt.clf()

    plt.figure(1)
    plt.xlim(0, len(ac))
    plt.plot(ac, ls="-", lw=1, color="r", label="actor网络损失值")
    plt.legend(loc=1)
    plt.xlabel("训练次数/100次")
    plt.ylabel("平均损失值")
    plt.savefig("actor.png")

    plt.show()

    plt.figure(2)
    plt.xlim(0, len(cr))
    plt.plot(cr, ls="-", lw=1, color="b", label="critic网络损失值")
    plt.legend(loc=1)
    plt.xlabel("训练次数/100次")
    plt.ylabel("平均损失值")
    plt.savefig("critic.png")

    plt.show()

    plt.figure(3)
    plt.xlim(0, len(re))
    plt.plot(re, ls="-", lw=1, color="g", label="reward奖励值")
    plt.legend(loc=1)
    plt.xlabel("训练次数/100次")
    plt.ylabel("平均奖励值")
    plt.savefig("reward.png")

    plt.show()


def validate(
    data_loader,
    actor,
    max_load,
    land_size,
    reward_fn,
    render_fn=None,
    save_dir=".",
    num_plot=5,
):
    """用于监测验证集的验证过程，并选择是否将解绘制成图"""

    actor.eval()

    if not os.path.exists(save_dir):
        os.makedirs(save_dir)

    rewards = []
    for batch_idx, batch in enumerate(data_loader):

        static, dynamic, areas, x0 = batch

        static = static.to(device)
        dynamic = dynamic.to(device)
        areas = areas.to(device)
        x0 = x0.to(device) if len(x0) > 0 else None

        with torch.no_grad():
            tour_indices, _ = actor.forward(static, dynamic, x0)

        reward = (
            reward_fn(static, areas, tour_indices, max_load, land_size).mean().item()
        )
        rewards.append(reward)

        if render_fn is not None and batch_idx < num_plot:
            f = open(save_dir + "/path.txt", "w")

            f.write(str(torch.cat((static, dynamic), dim=1)) + "\n")
            f.write(str(tour_indices % (tour_indices.size(1) + 1)) + "\n")
            f.write(str(1 + tour_indices // (tour_indices.size(1) + 1)))

            f.close()

            name = "batch%d_%2.4f.png" % (batch_idx, reward)
            path = os.path.join(save_dir, name)
            render_fn(static, tour_indices, path)

    actor.train()
    return np.mean(rewards)


def val_validate(actor, reward_fn):

    actor.eval()

    headers = ["退化区域坐标x", "退化区域坐标y", "可修复面积", "退化程度"]
    rows = []
    x = []
    y = []
    ar = []
    de = []
    # ar = torch.randint(10, 36, (44,)).tolist()
    # de = torch.randint(3, 9, (44,)) / 10.
    # de = de.tolist()

    torch.manual_seed(12345)
    torch.cuda.manual_seed_all(12345)

    with open("data.csv", "w", encoding="utf8", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(headers)
        writer.writerows(rows)


def test_validate(actor, reward_fn, max_load=1.5e3):

    actor.eval()

    # 新建测试数据
    headers = ["退化区域坐标x", "退化区域坐标y", "可修复面积", "退化程度"]
    rows = []
    x = []
    y = []
    ar = []
    de = []
    # ar = torch.randint(10, 36, (44,)).tolist()
    # de = torch.randint(3, 9, (44,)) / 10.
    # de = de.tolist()

    torch.manual_seed(12345)
    torch.cuda.manual_seed_all(12345)

    for i in range(4):
        x.append(torch.rand(11).tolist())
        y.append(torch.rand(11).tolist())
        ar.append(torch.randint(10, 36, (11,)).tolist())
        tmp = torch.randint(3, 9, (11,)) / 10.0
        de.append(tmp.tolist())

    x_ = sum(x, [])
    y_ = sum(y, [])
    ar_ = sum(ar, [])
    de_ = sum(de, [])

    for i in range(44):
        rows.append([str(x_[i]), str(y_[i]), str(ar_[i]), str(round(de_[i], 1))])

    with open("data.csv", "w", encoding="utf8", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(headers)
        writer.writerows(rows)

    # # k-means聚类
    N_CLUSTERS = 4  # 类簇的数量
    MARKERS = ["*", "v", "+", "^", "s", "x", "o"]  # 标记样式（绘图）
    COLORS = ["r", "g", "m", "c", "y", "b", "orange"]  # 标记颜色（绘图）
    LINESTYLE = ["-", "--", "-.", ":"]
    # # DATA_PATH = './data/China_cities.csv'              # 数据集路径

    df = pd.read_csv("data.csv")

    d = df.drop("可修复面积", axis=1)
    d = d.drop("退化程度", axis=1)

    x_np = np.array(d)  # 将x转化为numpy数组

    model = KMeans(N_CLUSTERS)  # 构建聚类器
    model.fit(d)  # 训练聚类器

    labels = model.labels_  # 获取聚类标签

    # # print(silhouette_samples(x, labels))  # 获取所有样本的轮廓系数
    # # print(silhouette_score(x, labels))      # 获取聚类结果总的轮廓系数

    # # print(model.cluster_centers_)	# 输出类簇中心

    # # for i in range(N_CLUSTERS):
    # #     print(f" CLUSTER-{i+1} ".center(60, '='))
    # #     print(df[labels == i])

    plt.clf()
    plt.figure(figsize=(9, 6))
    plt.title("k-means地图初始分配聚类图", fontsize=22)
    plt.xlabel("", fontsize=18)
    plt.ylabel("", fontsize=18)
    plt.xlim(0, 1)  # x轴的刻度范围
    plt.ylim(0, 1)  # y轴的刻度范围
    plt.axhline(0.5, color=COLORS[0], lw=1, linestyle="--", alpha=0.5)
    plt.axvline(0.5, color=COLORS[0], lw=1, linestyle="--", alpha=0.5)

    for i in range(N_CLUSTERS):
        members = labels == i  # members是一个布尔型数组
        plt.scatter(
            x_np[members, 1],
            x_np[members, 0],
            marker=MARKERS[i],  # 标记样式
            c=COLORS[i],  # 标记颜色
        )  # 绘制散点图

    # plt.grid()
    plt.axhline(0, color=COLORS[4], lw=2, linestyle="--", alpha=0.5)
    plt.axvline(0, color=COLORS[4], lw=2, linestyle="--", alpha=0.5)
    plt.show()
    plt.savefig("test1.png")

    plt.clf()

    plt.figure(figsize=(10, 6))
    plt.xlim(-350, 350, 50)  # x轴的刻度范围
    plt.ylim(-350, 350, 50)  # y轴的刻度范围
    plt.xlabel("", fontproperties="AR PL UKai CN")  # x轴的标题
    plt.ylabel("", fontproperties="AR PL UKai CN")  # y轴的标题

    # first_time = True
    # traj = [[] for i in range(4)]
    # traj_t = [[] for i in range(4)]
    # res_t = [[] for i in range(4)]
    # # reward_1, reward_2 = 0
    # tmp_r = [[] for i in range(4)]
    # while True:
    #     for i in range(N_CLUSTERS):
    #         # tmp = torch.tensor(df[labels == i].values) if first_time else tmp_r[i]
    #         tmp = torch.tensor(df[labels == i].values)
    #         st = 0
    #         if first_time:
    #             for j in range(len(tmp) - 1):
    #                 st = j + 1 if torch.sqrt(pow(tmp[j][0], 2) + pow(tmp[j][1], 2)) > torch.sqrt(pow(tmp[j+1][0], 2) + pow(tmp[j+1][1], 2)) else j

    #             tp = tmp[st]
    #             tmp[st] = tmp[0]
    #             tmp[0] = tp

    #         df.drop([st])

    #         dem = (1e4 * tmp[:, 2] * (1 + tmp[:, 3]) ** 2) / float(max_load)
    #         de_t = 2 * (tmp[:, 3] -0.3)

    #         static = torch.cat([tmp[:,0:2], de_t.unsqueeze(1)],dim = 1).permute(1, 0).unsqueeze(0).float().to(device)
    #         dynamic = torch.cat([torch.ones(len(dem)).unsqueeze(1), dem.unsqueeze(1)], dim = 1).permute(1, 0).unsqueeze(0).float().to(device)
    #         areas = tmp[:, 2].float().unsqueeze(0).to(device)
    #         x0 = static[:, :, 0].float().unsqueeze(2).to(device)

    #         with torch.no_grad():
    #             tour_indices, _ = actor.forward(static, dynamic, x0)

    #     #     if first_time:
    #     #         reward_1 = reward_fn(static, areas, tour_indices).mean().item()
    #     #         tour_1 = tour_indices
    #     #     else:
    #     #         reward_2 = reward_fn(static, areas, tour_indices).mean().item()

    #     #     traj[i].append(tour_indices[0].tolist()[0][0])
    #         traj[i] = tour_indices[0].tolist()
    #         traj_t[i] = (tour_indices[0] % (len(traj[i]) + 1)).tolist()
    #         res_t[i] = [0] + (tour_indices[0] // (len(traj[i]) + 1)).tolist()

    #         # print(traj_t[i])

    #         l = [[0, 0, 0]]
    #         for z in traj_t[i]:
    #             l.append([700 * float(tmp[z][0]) -350, 700 * float(tmp[z][1]) -350, z])
    #         l.append([0, 0, 0])

    #         #绘制各个点及点所代表地点名称
    #         for j in range(len(l)-1):
    #             if j == 0:
    #                 plt.text(l[j][0],l[j][1], '地面控制中心', color='#0085c3', fontproperties="AR PL UKai CN")
    #             else:
    #                 # plt.text(l[j][0],l[j][1],'区域'+str(l[j][2])+', 修复面积'+str(res_t[i][j]),color='#0085c3',fontproperties="AR PL UKai CN")
    #                 plt.text(l[j][0],l[j][1],str(l[j][2])+': 修复'+str(res_t[i][j]),color='#0085c3',fontproperties="AR PL UKai CN")
    #             tmp_r[i], = plt.plot(l[j][0],l[j][1], marker=MARKERS[i], color=COLORS[i])
    #         #连接各个点
    #         for j in range(len(l)-1):
    #             start = (l[j][0],l[j+1][0])
    #             end = (l[j][1],l[j+1][1])
    #             plt.plot(start,end,linestyle=LINESTYLE[i],color=COLORS[i])

    #         # plt.show()
    #         # plt.savefig('t'+str(i))

    #     #     if tmp:
    #     #         tmp_r.append(tmp[1:])
    #     #     else:
    #     #         tmp_r.append([])

    #     #     if not first_time:
    #     #         if reward_2 > reward_1:

    #     # if not len(sum(traj, [])) == 40:
    #     #     break

    #     # print(traj_t)
    #     first_time = False
    #     plt.legend(tmp_r, ['UAV1', 'UAV2', 'UAV3', 'UAV4'],loc='upper right')
    #     plt.axhline(0, color=COLORS[4], lw=2, linestyle = '--', alpha=0.5)
    #     plt.axvline(0, color=COLORS[4], lw=2, linestyle = '--', alpha=0.5)
    #     plt.show()
    #     plt.savefig('test2.png')
    #     break


# plt.clf()


def train(
    actor,
    critic,
    max_load,
    land_size,
    task,
    num_nodes,
    reward_fn,
    render_fn,
    batch_size,
    actor_lr,
    critic_lr,
    max_grad_norm,
    **kwargs
):
    """构建主要的actor和critic网络，并进行训练"""

    now = "%s" % datetime.datetime.now().time()
    now = now.replace(":", "_")
    save_dir = os.path.join(task, "%d" % num_nodes, now)

    checkpoint_dir = os.path.join(save_dir, "checkpoints")
    if not os.path.exists(checkpoint_dir):
        os.makedirs(checkpoint_dir)
    # 使用 Adam 优化器初始化了 actor 和 critic 网络的优化器。
    actor_optim = optim.Adam(actor.parameters(), lr=actor_lr)
    critic_optim = optim.Adam(critic.parameters(), lr=critic_lr)
    # 最大值初始化为无穷大
    best_reward = np.inf

    ac, cr, re = [], [], []

    for epoch in tqdm(range(100)):  # 添加进度条
        # 训练数据生成
        train_data = VehicleRoutingDataset( 
            args.train_size, args.num_nodes, max_load, args.num_areas, args.seed
        )
        # 验证数据生成
        valid_data = VehicleRoutingDataset(
            args.valid_size, args.num_nodes, max_load, args.num_areas, args.seed + 1
        )

        train_loader = DataLoader(train_data, batch_size, True, num_workers=0)
        valid_loader = DataLoader(valid_data, batch_size, False, num_workers=0)

        actor.train()
        critic.train()

        times, losses, rewards, critic_rewards, critic_losses = [], [], [], [], []

        epoch_start = time.time()
        start = epoch_start

        for batch_idx, batch in enumerate(train_loader):

            static, dynamic, areas, x0 = batch

            static = static.to(device)
            dynamic = dynamic.to(device)
            areas = areas.to(device)
            x0 = x0.to(device) if len(x0) > 0 else None

            # 完整训练集的前向传播，得到路径索引和对数概率
            tour_indices, tour_logp = actor(static, dynamic, x0)

            # 将经过一条所有点的对数概率求和
            reward = reward_fn(static, areas, tour_indices, max_load, land_size)

            # 评论家网络估计路径奖励
            critic_est = critic(static, dynamic).view(-1)

            advantage = reward - critic_est
            actor_loss = torch.mean(advantage.detach() * tour_logp.sum(dim=1))
            critic_loss = torch.mean(advantage**2)
            # 反向传播
            actor_optim.zero_grad()
            actor_loss.backward()
            torch.nn.utils.clip_grad_norm_(actor.parameters(), max_grad_norm)
            actor_optim.step()
            # 反向传播
            critic_optim.zero_grad()
            critic_loss.backward()
            torch.nn.utils.clip_grad_norm_(critic.parameters(), max_grad_norm)
            critic_optim.step()

            critic_rewards.append(torch.mean(critic_est.detach()).item())
            rewards.append(torch.mean(reward.detach()).item())
            losses.append(torch.mean(actor_loss.detach()).item())
            critic_losses.append(torch.mean(critic_loss.detach()).item())

            if (batch_idx + 1) % 100 == 0:
                end = time.time()
                times.append(end - start)
                start = end

                mean_loss = np.mean(losses[-100:])
                mean_reward = np.mean(rewards[-100:])

                ac.append(mean_loss)
                re.append(mean_reward)
                cr.append(np.mean(critic_losses[-100:]))

                print(
                    "  Batch %d/%d, reward: %2.3f, loss: %2.4f, took: %2.4fs"
                    % (batch_idx, len(train_loader), mean_reward, mean_loss, times[-1])
                )

        mean_loss = np.mean(losses)
        mean_reward = np.mean(rewards)

        # 保存训练权重
        epoch_dir = os.path.join(checkpoint_dir, "%s" % epoch)
        if not os.path.exists(epoch_dir):
            os.makedirs(epoch_dir)

        save_path = os.path.join(epoch_dir, "actor.pt")
        torch.save(actor.state_dict(), save_path)

        save_path = os.path.join(epoch_dir, "critic.pt")
        torch.save(critic.state_dict(), save_path)

        # 保存验证集绘图
        valid_dir = os.path.join(save_dir, "%s" % epoch)

        mean_valid = validate(
            valid_loader,
            actor,
            max_load,
            land_size,
            reward_fn,
            render_fn,
            valid_dir,
            num_plot=5,
        )

        # 保存最佳模型参数
        if mean_valid < best_reward:

            best_reward = mean_valid

            save_path = os.path.join(save_dir, "actor.pt")
            torch.save(actor.state_dict(), save_path)

            save_path = os.path.join(save_dir, "critic.pt")
            torch.save(critic.state_dict(), save_path)

        print(
            "Mean epoch loss/reward: %2.4f, %2.4f, %2.4f, took: %2.4fs "
            "(%2.4fs / 100 batches)\n"
            % (
                mean_loss,
                mean_reward,
                mean_valid,
                time.time() - epoch_start,
                np.mean(times),
            )
        )

    train_plot(ac, cr, re)


def train_vrp(args):

    ######################

    MAX_DEMAND = args.num_areas
    STATIC_SIZE = 3
    DYNAMIC_SIZE = 2

    # max_load = LOAD_DICT[args.num_nodes]
    max_load = args.max_load
    land_size = args.land_size

    try:
        del actor
        del critic
    except:
        pass

    test_data = VehicleRoutingDataset(
        args.valid_size, args.num_nodes, max_load, MAX_DEMAND, args.seed + 2
    )

    actor = DRL4TSP(
        STATIC_SIZE,
        DYNAMIC_SIZE,
        args.hidden_size,
        args.num_areas,
        max_load,
        args.num_layers,
        args.dropout,
        test_data.update_dynamic,
        test_data.update_mask,
    ).to(device)

    critic = StateCritic(STATIC_SIZE, DYNAMIC_SIZE, args.hidden_size).to(device)

    kwargs = vars(args)
    kwargs["reward_fn"] = vrp.reward
    kwargs["render_fn"] = vrp.render

    if args.checkpoint:
        path = os.path.join(args.checkpoint, "actor.pt")
        actor.load_state_dict(torch.load(path, device))

        path = os.path.join(args.checkpoint, "critic.pt")
        critic.load_state_dict(torch.load(path, device))

    if not args.test:
        train(actor, critic, **kwargs)

    test_dir = "test"
    test_loader = DataLoader(test_data, args.batch_size, False, num_workers=0)
    out = validate(
        test_loader,
        actor,
        max_load,
        land_size,
        vrp.reward,
        vrp.render,
        test_dir,
        num_plot=5,
    )

    print("Average tour length: ", out)

    # test_validate(actor, vrp.reward, maxload)


if __name__ == "__main__":
    # print( torch.device('cuda' if torch.cuda.is_available() else 'cpu'))

    parser = argparse.ArgumentParser(description="Combinatorial Optimization")
    parser.add_argument("--seed", default=12345, type=int)
    parser.add_argument("--checkpoint", default=None)
    parser.add_argument("--test", action="store_true", default=False)
    parser.add_argument("--task", default="vrp")
    parser.add_argument("--nodes", dest="num_nodes", default=20, type=int)
    parser.add_argument("--areas", dest="num_areas", default=20, type=int)
    parser.add_argument("--max_energy", dest="max_load", default=1.5e3, type=int)
    parser.add_argument("--land_size", dest="land_size", default=7, type=int)
    parser.add_argument("--actor_lr", default=5e-5, type=float)
    parser.add_argument("--critic_lr", default=5e-5, type=float)
    parser.add_argument("--max_grad_norm", default=2.0, type=float)
    parser.add_argument("--batch_size", default=512, type=int)
    parser.add_argument("--hidden", dest="hidden_size", default=128, type=int)
    parser.add_argument("--dropout", default=0.1, type=float)
    parser.add_argument("--layers", dest="num_layers", default=1, type=int)
    parser.add_argument("--train-size", default=512000, type=int)
    parser.add_argument("--valid-size", default=5120, type=int)

    args = parser.parse_args()

    if args.task == "vrp":
        train_vrp(args)
    else:
        raise ValueError("Task <%s> not understood" % args.task)
