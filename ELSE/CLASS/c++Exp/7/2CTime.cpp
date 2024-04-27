/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\7\2CTime.cpp
 * @Description: 设计 CTime 类
1、成员变量：hour、minute、second；
2、多个构造函数；
显示函数：Display()；
设置函数：SetHour(int hour)、SetMinute(int min)、 SetSecond(int sec)；
3、重载++运算符，模拟钟表走动，每次走一秒，每60 秒进一分钟，秒又从0 开始计算；每60 分进一小时，分钟从0 开始计算。

 */

#include <iostream>
using namespace std;

class CTime
{
private:
    int hour, minute, second; // 小时、分钟、秒钟

public:
    CTime()
    {
        hour = 0;
        minute = 0;
        second = 0;
    }
    CTime(int h, int m, int s)
    {
        hour = h;
        minute = m;
        second = s;
    }
    CTime(const CTime &t)
    {
        hour = t.hour;
        minute = t.minute;
        second = t.second;
    }
    void SetHour(int h)
    {
        hour = h;
    }
    void SetMinute(int m)
    {
        minute = m;
    }
    void SetSecond(int s)
    {
        second = s;
    }
    void Display()
    {
        cout << hour << ":" << minute << ":" << second << endl; // 输出小时、分钟和秒钟
    }
    CTime operator++(int)
    {
        CTime temp(*this);
        second++;
        if (second == 60)
        {
            second = 0;
            minute++;
            if (minute == 60)
            {
                minute = 0;
                hour++;
                if (hour == 24)
                {
                    hour = 0;
                }
            }
        }
        return temp;
    }
};

int main()
{
    CTime t1(13, 45, 39);
    cout << "Declare a time object t1:";
    t1.Display(); // 输出时间对象t1的值

    t1++; // 将时间对象t1递增1秒

    cout << "Time Object Increment:";
    t1.Display(); // 输出递增后的时间对象t1的值

    CTime t2(23, 58, 5);

    cout << "Declare the second time object t2:";
    t2.Display(); // 输出时间对象t2的值

    t2++; // 将时间对象t2递增1秒

    cout << "Time Object Increment:";
    t2.Display(); // 输出递增后的时间对象t2的值

    return 0;
}
