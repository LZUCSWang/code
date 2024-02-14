#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // 获取当前时间戳（秒和微秒）
    long long int unix_timestamp_s = tv.tv_sec;
    long long int unix_timestamp_us = tv.tv_usec;

    // 将微秒转换为纳秒
    long long int unix_timestamp_ns = unix_timestamp_s * 1000000000 + unix_timestamp_us * 1000;

    // 自行进行时间转换
    long long int unix_timestamp_beijing_s = unix_timestamp_s + 8 * 3600; // 北京时区偏移为+8小时

    // 计算星期几
    const char *days[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
    int day_of_week = (unix_timestamp_beijing_s / 86400 + 4) % 7; // 1970年1月1日是星期四，每天有86400秒

    // 格式化输出
    printf("%lld年 %02lld月 %02lld日 %s %02lld:%02lld:%02lld CST\n",
           unix_timestamp_beijing_s / 31536000 + 1970, // 年
           (unix_timestamp_beijing_s % 31536000) / 2592000 + 1, // 月
           (unix_timestamp_beijing_s % 2592000) / 86400, // 日
           days[day_of_week], // 星期几
           (unix_timestamp_beijing_s % 86400) / 3600, // 时
           (unix_timestamp_beijing_s % 3600) / 60, // 分
           unix_timestamp_beijing_s % 60 // 秒
    );

    return 0;
}
