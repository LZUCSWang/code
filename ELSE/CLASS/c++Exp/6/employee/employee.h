/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\6\employee\employee.h
 * @Description: employee类的头文件，包含友元函数DisplayEmployee的声明，以及employee类的声明
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "Date.h" // 包含"Date"头文件
#include <iostream>
using namespace std;

class employee
{
public:
    employee() {} // 默认构造函数

    // 带参数的构造函数
    employee(int id, const string &name, string gender, const Date &birth, const string &position, double salary);

    // 友元函数声明，用于显示员工信息
    friend void DisplayEmployee(const employee &e);

    // 获取员工薪资的虚函数
    virtual double GetMonthlySalary() const = 0;

protected:
    int id_;          // 员工ID
    string name_;     // 员工姓名
    string gender_;   // 员工性别
    Date birth_;      // 员工生日
    string position_; // 员工职位
    double salary_;   // 员工薪水
};

#endif
