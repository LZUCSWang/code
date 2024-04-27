/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\6\employee\Date.h
 * @Description: 
 */
#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date() {}

    /**
     * @brief 构造函数，用于初始化日期对象
     * @param year 年份
     * @param month 月份
     * @param day 日期
     */
    Date(int year, int month, int day);

    /**
     * @brief 设置年份
     * @param year 年份
     */
    void SetYear(int year);

    /**
     * @brief 设置月份
     * @param month 月份
     */
    void SetMonth(int month);

    /**
     * @brief 设置日期
     * @param day 日期
     */
    void SetDay(int day);

    /**
     * @brief 获取年份
     * @return 年份
     */
    int GetYear() const;

    /**
     * @brief 获取月份
     * @return 月份
     */
    int GetMonth() const;

    /**
     * @brief 获取日期
     * @return 日期
     */
    int GetDay() const;

private:
    int year_; // 年份
    int month_; // 月份
    int day_; // 日期
};
#endif
