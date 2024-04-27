/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Salesman.h
 * @Description: 销售员类头文件
 */

#ifndef SALESMAN_H
#define SALESMAN_H

#include "Employee.h"

// Salesman 类
class Salesman : virtual public Employee
{
public:
    Salesman() {} // 默认构造函数
    Salesman(int id, const string &name, char gender, const Date &birth, const string &department, double sales); // 带参数的构造函数
    double pay() const override; // 重写虚函数，计算销售员的工资
    void display() const override; // 重写虚函数，显示销售员的信息
    void promote(double salary) const override; // 重写虚函数，提升销售员的工资

protected:
    string department_; // 销售部门
    double sales_; // 销售额
};

#endif
