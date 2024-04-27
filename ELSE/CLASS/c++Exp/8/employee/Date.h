/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Date.h
 * @Description: 日期类头文件
 */

#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date() {} // 默认构造函数
    Date(int year, int month, int day); // 带参数的构造函数
    void SetYear(int year); // 设置年份
    void SetMonth(int month); // 设置月份
    void SetDay(int day); // 设置日期
    int GetYear() const; // 获取年份
    int GetMonth() const; // 获取月份
    int GetDay() const; // 获取日期

private:
    int year_; // 年份
    int month_; // 月份
    int day_; // 日期
};
#endif
