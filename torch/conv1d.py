import torch
import torch.nn as nn
import matplotlib.pyplot as plt

# 输入数据
batch_size = 1
seq_length = 10
input_channels = 3
input_sequence = torch.randn(batch_size, input_channels, seq_length)

# 卷积层
out_channels = 4
kernel_size = 3
conv1d_layer = nn.Conv1d(
    in_channels=input_channels, out_channels=out_channels, kernel_size=kernel_size
)

# 执行卷积操作
output_sequence = conv1d_layer(input_sequence)

# 计算子图总数
total_subplots = (
    input_channels + 1 + out_channels
)  # 输入数据通道数 + 卷积核 + 输出数据通道数

# 可视化卷积过程
plt.figure(figsize=(12, 6))

# 绘制输入数据
for i in range(input_channels):
    plt.subplot(total_subplots, 1, i + 1)
    plt.title(f"Input Channel {i + 1}")
    plt.imshow(input_sequence[0, i].unsqueeze(0).numpy(), cmap="viridis", aspect="auto")
    plt.xticks(range(seq_length))
    plt.yticks([])
    if i == 0:
        plt.colorbar()

# 绘制卷积核
plt.subplot(total_subplots, 1, input_channels + 1)
plt.title("Convolutional Kernel")
plt.imshow(conv1d_layer.weight.data[:, 0, :].numpy(), cmap="viridis", aspect="auto")
plt.xticks(range(kernel_size), labels=[f"Index {i}" for i in range(kernel_size)])
plt.yticks(
    range(out_channels), labels=[f"Output Channel {i + 1}" for i in range(out_channels)]
)
plt.colorbar()

# 绘制输出数据
for i in range(out_channels):
    plt.subplot(total_subplots, 1, input_channels + 2 + i)
    plt.title(f"Output Channel {i + 1}")
    plt.imshow(
        output_sequence[0, i].unsqueeze(0).detach().numpy(),
        cmap="viridis",
        aspect="auto",
    )
    plt.xticks(range(seq_length))
    plt.yticks([])
    if i == 0:
        plt.colorbar()

plt.tight_layout()
plt.show()

# 打印形状
print("Input shape:", input_sequence.shape)
print("Output shape:", output_sequence.shape)
  