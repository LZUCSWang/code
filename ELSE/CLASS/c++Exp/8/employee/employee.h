/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\employee.h
 * @Description: 员工类头文件
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "Date.h"
#include <iostream>
#include <map>
using namespace std;

class Employee
{
public:
    // 默认构造函数
    Employee() {}

    // 构造函数，初始化员工信息
    Employee(int id, const string &name, char gender, const Date &birth, const string &position, double salary);

    // 纯虚函数，显示员工信息
    virtual void display() const = 0;

    // 纯虚函数，计算员工工资
    virtual double pay() const = 0;

    // 纯虚函数，晋升员工并调整薪资
    virtual void promote(double salary) const = 0;

    // 友元函数，用于显示员工信息
    friend void DisplayEmployee(const Employee &e);

protected:
    int id_;          // 员工编号
    string name_;     // 员工姓名
    char gender_;     // 员工性别
    Date birth_;      // 员工出生日期
    string position_; // 员工职位
    double salary_;   // 员工薪资
};

#endif
