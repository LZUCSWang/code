/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Date.cpp
 * @Description: 日期类实现文件
 */

#include "date.h"

// 构造函数，初始化日期
Date::Date(int year, int month, int day) : year_(year), month_(month), day_(day) {}

// 设置年份
void Date::SetYear(int year)
{
    year_ = year;
}

// 设置月份
void Date::SetMonth(int month)
{
    month_ = month;
}

// 设置日期
void Date::SetDay(int day)
{
    day_ = day;
}

// 获取年份
int Date::GetYear() const
{
    return year_;
}

// 获取月份
int Date::GetMonth() const
{
    return month_;
}

// 获取日期
int Date::GetDay() const
{
    return day_;
}
