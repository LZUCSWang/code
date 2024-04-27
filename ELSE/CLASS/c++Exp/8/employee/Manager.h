/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Manager.h
 * @Description: 管理人员类头文件
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

// Manager 类
class Manager : virtual public Employee
{
public:
    Manager() {} // 默认构造函数
    Manager(int id, const string &name, char gender, const Date &birth); // 构造函数
    double pay() const override; // 计算工资
    void display() const override; // 显示员工信息
    void promote(double salary) const override; // 提升薪水
};

#endif
