/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\6\employee\Date.cpp
 * @Description: 
 */
#include "date.h"

Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day)
{
    // 构造函数，用于初始化日期对象
    // 参数：year 年份，month 月份，day 日期
    // 将传入的参数赋值给对应的成员变量
}

void Date::SetYear(int year)
{
    // 设置年份
    // 参数：year 年份
    // 将传入的年份设置为对象的年份
    year_ = year;
}

void Date::SetMonth(int month)
{
    // 设置月份
    // 参数：month 月份
    // 将传入的月份设置为对象的月份
    month_ = month;
}

void Date::SetDay(int day)
{
    // 设置日期
    // 参数：day 日期
    // 将传入的日期设置为对象的日期
    day_ = day;
}

int Date::GetYear() const
{
    // 获取年份
    // 返回值：年份
    // 返回对象的年份
    return year_;
}

int Date::GetMonth() const
{
    // 获取月份
    // 返回值：月份
    // 返回对象的月份
    return month_;
}

int Date::GetDay() const
{
    // 获取日期
    // 返回值：日期
    // 返回对象的日期
    return day_;
}
