/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Technician.h
 * @Description: 技术人员类头文件
 */

#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "Employee.h"

// Technician 类
class Technician : public Employee
{
public:
    Technician() {} // 默认构造函数
    Technician(int id, const string &name, char gender, const Date &birth, double work_time); // 带参数的构造函数
    double pay() const override; // 计算工资的函数
    void display() const override; // 显示技术人员信息的函数
    void promote(double salary) const override; // 职位晋升的函数

private:
    double work_time_; // 工作时长
};

#endif
