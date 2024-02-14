<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\4\1date.cpp
 * @Description: 用结构体存储日期，计算某天是一年中的第几天
 */

#include <iostream>
=======
#include <iostream>

>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
using namespace std;

struct Date
{
    int year;
    int month;
    int day;
};

<<<<<<< HEAD
/**
 * @description: 判断是否为闰年
 * @param {int} year 年份
 * @return {*} 是否为闰年
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
bool isLeapYear(int year) // 判断是否为闰年
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

<<<<<<< HEAD
/**
 * @description: 计算某年某月的天数
 * @param {int} year
 * @param {int} month
 * @return {*} 天数
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
int daysOfMonth(int year, int month) // 计算某年某月的天数
{
    switch (month)
    {
    case 2:
        return isLeapYear(year) ? 29 : 28;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    default:
        return 31;
    }
}

int main()
{
    Date date;
<<<<<<< HEAD
    cout << sizeof(date) << endl;
    // 判断输入的日期是否合法
    while (true)
    {
        cout << "Input year, month, day: ";
        cin >> date.year >> date.month >> date.day;
        if (date.year == 0 && date.month == 0 && date.day == 0)
        {
            break;
        }
        if (date.year < 0 || date.month < 1 || date.month > 12 || date.day < 1 || date.day > daysOfMonth(date.year, date.month))
        {
            cout << "Invalid date" << endl;
            continue;
        }
        int days = 0;
        for (int i = 1; i < date.month; i++)
        {
            days += daysOfMonth(date.year, i); // 计算前几个月的天数
        }
        days += date.day; // 加上当月的天数

        cout << date.year << "." << date.month << "." << date.day
             << " is the " << days << "th day of the year" << endl;
    }
=======
    cout << "Input year, month, day: ";
    cin >> date.year >> date.month >> date.day;

    // 判断输入的日期是否合法
    if (date.year < 0 || date.month < 1 || date.month > 12 || date.day < 1 || date.day > daysOfMonth(date.year, date.month))
    {
        cout << "Invalid date" << endl;
        return 0;
    }
    int days = 0;
    for (int i = 1; i < date.month; i++)
    {
        days += daysOfMonth(date.year, i); // 计算前几个月的天数
    }
    days += date.day; // 加上当月的天数

    cout << date.year << "." << date.month << "." << date.day
         << "is the " << days << "th day of the year" << endl;
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    delete &date;
    return 0;
}
