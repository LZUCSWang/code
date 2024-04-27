/*
@Author: 王贤义
 * @FilePath: \code\C+++C\c++\9\employee\Date.h
@Description: 日期类头文件
*/
#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date() {} // 默认构造函数
    Date(int year, int month, int day);
    // 构造函数，用于初始化日期对象

    /**
     * @description: 设置年份
     * @param {int} year 年份
     * @return {*}
     */
    void SetYear(int year);

    /**
     * @description: 设置月份
     * @param {int} month 月份
     * @return {*}
     */
    void SetMonth(int month);

    /**
     * @description: 设置日期
     * @param {int} day 日期
     * @return {*}
     */
    void SetDay(int day);

    /**
     * @description: 获取年份
     * @return {int} 年份
     */
    int GetYear() const;

    /**
     * @description: 获取月份
     * @return {int} 月份
     */
    int GetMonth() const;

    /**
     * @description: 获取日期
     * @return {int} 日期
     */
    int GetDay() const;

private:
    int year_;  // 年份
    int month_; // 月份
    int day_;   // 日期
};

#endif