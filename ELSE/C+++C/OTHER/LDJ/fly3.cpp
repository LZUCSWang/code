#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

#define SAMPLE_RATE 1000.0   // 采样率
#define CUTOFF_FREQ 50.0     // 截止频率
#define Q_FACTOR 0.707        // Q因子

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
    double omega_c = 2.0 * CV_PI * CUTOFF_FREQ / SAMPLE_RATE;
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

    // 创建输入信号（示例中使用一个简单的正弦波）
    int numSamples = 1000;
    Mat inputSignal(1, numSamples, CV_64F);
    for (int i = 0; i < numSamples; ++i) {
        inputSignal.at<double>(i) = sin(2.0 * CV_PI * 10.0 * i / SAMPLE_RATE);
    }

    // 创建输出信号
    Mat outputSignal(1, numSamples, CV_64F);

    // 应用滤波器并保存输出
    for (int i = 0; i < numSamples; ++i) {
        double filtered = applyFilter(&filter, inputSignal.at<double>(i));
        outputSignal.at<double>(i) = filtered;
    }

    // 绘制输入和输出信号
    namedWindow("Input Signal", WINDOW_AUTOSIZE);
    namedWindow("Filtered Signal", WINDOW_AUTOSIZE);
    imshow("Input Signal", inputSignal);
    imshow("Filtered Signal", outputSignal);
    waitKey(0);

    return 0;
}