/*
@Author: 王贤义
 * @FilePath: \code\C+++C\c++\9\employee\employee.h
@Description: 员工类头文件
*/
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "Date.h"
#include <iostream>
#include <fstream>
using namespace std;

class employee
{
public:
    employee() {} // 默认构造函数
    employee(int id, const string &name, char gender, const Date &birth, const string &position, double salary);
    // 构造函数，用于初始化员工对象

    /**
     * @description: 显示员工信息
     * @param {employee} &e 员工对象引用
     * @param {ostream} &fout 输出流对象引用
     * @return {*}
     */
    friend void DisplayEmployee(const employee &e, ostream &fout);
    // 友元函数，用于显示员工信息

    /**
     * @description: 获取员工月薪
     * @return {double} 员工月薪
     */
    virtual double GetMonthlySalary() const = 0;
    // 纯虚函数，获取员工月薪

    /**
     * @description: 显示员工信息
     * @param {ostream} &fout 输出流对象引用
     * @return {*}
     */
    virtual void Display(ostream &fout) = 0;
    // 纯虚函数，显示员工信息

protected:
    int id_;          // 员工ID
    string name_;     // 员工姓名
    char gender_;     // 员工性别
    Date birth_;      // 员工出生日期
    string position_; // 员工职位
    double salary_;   // 员工薪水
};

#endif