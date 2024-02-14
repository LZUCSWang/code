#include <stdio.h>
#include <math.h>

#define SAMPLE_RATE 1000.0   // 采样率
#define CUTOFF_FREQ 100.0    // 截止频率
#define Q_FACTOR 0.707        // Q因子
#define M_PI 3.14159265358979323846  // 圆周率
// 巴特沃斯低通滤波器结构体
typedef struct {
    double x[2];   // 输入历史值
    double y[2];   // 输出历史值
    double a1, a2, b0, b1, b2;  // 滤波器系数
} ButterworthFilter;

// 初始化滤波器
void initFilter(ButterworthFilter *filter) {
    filter->x[0] = filter->x[1] = 0.0;
    filter->y[0] = filter->y[1] = 0.0;

    // 计算滤波器系数
    double omega_c = 2.0 * M_PI * CUTOFF_FREQ / SAMPLE_RATE;
    double alpha = sin(omega_c) / (2.0 * Q_FACTOR);
    double cos_omega_c = cos(omega_c);

    filter->b0 = (1.0 - cos_omega_c) / 2.0;
    filter->b1 = 1.0 - cos_omega_c;
    filter->b2 = (1.0 - cos_omega_c) / 2.0;
    filter->a1 = -2.0 * cos_omega_c;
    filter->a2 = 1.0 - alpha;
}

// 应用滤波器
double applyFilter(ButterworthFilter *filter, double input) {
    double output = filter->b0 * input + filter->b1 * filter->x[0] + filter->b2 * filter->x[1]
                  - filter->a1 * filter->y[0] - filter->a2 * filter->y[1];

    filter->x[1] = filter->x[0];
    filter->x[0] = input;
    filter->y[1] = filter->y[0];
    filter->y[0] = output;

    return output;
}

int main() {
    // 创建并初始化滤波器
    ButterworthFilter filter;
    initFilter(&filter);

    // 输入信号
    double inputSignal[] = {1.0, 0.5, 0.2, -0.3, -0.7, -0.5, 0.2, 0.8, 1.0, 0.6};
    int numSamples = sizeof(inputSignal) / sizeof(inputSignal[0]);

    // 应用滤波器并输出结果
    printf("Input Signal: ");
    for (int i = 0; i < numSamples; ++i) {
        double filtered = applyFilter(&filter, inputSignal[i]);
        printf("%.4f ", filtered);
    }
    getchar();
    return 0;
}