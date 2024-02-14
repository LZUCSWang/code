#!/usr/bin/env python
# -*- coding: utf-8 -*-

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm

from dataset import DataGenerator  # 导入数据集生成器
from actor import Actor  # 导入Actor（指针网络模型）
from config import get_config, print_config  # 导入配置相关的函数

from tensorflow.python import debug as tf_dbg  # 导入TensorFlow调试器
def main():
    # a = tf.test.is_gpu_available()
    # print(a)  # 检查GPU是否可用
    # return
    # 获取运行配置
    config, _ = get_config()
    print_config()

    # 从配置构建TensorFlow图
    print("Building graph...")
    actor = Actor(config)  # 创建Actor（指针网络）对象

    # 创建用于保存和恢复模型的Saver对象
    variables_to_save = [v for v in tf.global_variables() if 'Adam' not in v.name]
    saver = tf.train.Saver(var_list=variables_to_save, keep_checkpoint_every_n_hours=1.0)

    rewards = []  # 用于存储训练期间的奖励

    result_pos_list = []  # 存储测试模式下的路径结果

    print("Starting session...")
    with tf.Session() as sess:
        # 运行初始化操作
        # sess=tf_dbg.LocalCLIDebugWrapperSession(sess)
        sess.run(tf.global_variables_initializer())

        # 加载模型
        if config.restore_model is True:
            saver.restore(sess, config.restore_from)
            print("Model restored.")

        training_set = DataGenerator(config)  # 创建数据集生成器对象

        # 训练模式
        if config.training_mode:
            print("Starting training...")
            for i in tqdm(range(config.iteration)):
                # 获取feed字典
                input_batch = training_set.train_batch()
                feed = {actor.input_: input_batch}

                # 前向传播和训练步骤
                positions, reward, train_step1, train_step2, encoder_output, masked_scores, scores_g, attention_g,glimpse,encoded_ref,encoded_query,scores,scores1,W_ref_g,W_q_g,v_g,W_ref,W_q,v = sess.run(
                    [actor.positions, actor.reward, actor.train_step1, actor.train_step2, actor.ptr.encoder_output,actor.ptr.masked_scores,actor.ptr.scores_g, actor.ptr.attention_g,actor.ptr.glimpse,actor.ptr.encoded_ref,actor.ptr.encoded_query,actor.ptr.scores,actor.ptr.scores1,actor.ptr.W_ref_g,actor.ptr.W_q_g,actor.ptr.v_g,actor.ptr.W_ref,actor.ptr.W_q,actor.ptr.v],
                    feed_dict=feed)

                rewards.append(np.mean(reward))

                if i % 100 == 0 and i != 0:
                    print("after " + str(i) + " rounds training, Travel Distance is: " + str(rewards[-1]))

                # 每1000轮保存模型变量到磁盘
                if i % 1000 == 0 and i != 0:
                    save_path = saver.save(sess, config.save_to)
                    print("Model saved in file: %s" % save_path)

            print("Training COMPLETED !")
            save_path = saver.save(sess, config.save_to)
            print("Model saved in file: %s" % save_path)

        # 测试模式
        else:
            # 获取测试数据
            input_batch = training_set.test_batch()
            feed = {actor.input_: input_batch}

            # 采样解决方案
            positions, _, _, _ = sess.run(
                [actor.positions, actor.reward, actor.train_step1, actor.train_step2],
                feed_dict=feed)

            city = input_batch[0]
            position = positions[0]
            result_pos_list = city[position, :]

    # 解决中文显示问题
    plt.rcParams['font.sans-serif'] = ['KaiTi']  # 指定默认字体
    plt.rcParams['axes.unicode_minus'] = False  # 解决保存图像时负号'-'显示为方块的问题
    plt.rcParams['savefig.dpi'] = 400  # 图片像素
    plt.rcParams['figure.dpi'] = 400  # 分辨率

    if config.training_mode:
        fig = plt.figure()
        plt.plot(list(range(len(rewards))), rewards, c='red')
        plt.title(u"效果曲线")
        plt.xlabel('轮数')
        plt.legend()
        fig.show()
    else:
        fig = plt.figure()
        plt.plot(result_pos_list[:, 0], result_pos_list[:, 1], 'o-r')
        plt.title(u"路线")
        plt.legend()
        fig.show()

if __name__ == "__main__":
    main()
