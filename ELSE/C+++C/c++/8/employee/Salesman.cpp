/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Salesman.cpp
 * @Description: 销售员类实现文件
 */

#include "Salesman.h"
extern map<string, double> department_map;

// Salesman 类
Salesman::Salesman(int id, const string &name, char gender, const Date &birth, const string &department, double sales) : department_(department), sales_(sales)
{
    this->id_ = id; // 设置销售员的ID
    this->name_ = name; // 设置销售员的姓名
    this->gender_ = gender; // 设置销售员的性别
    this->birth_ = birth; // 设置销售员的出生日期
    this->position_ = "Salesman"; // 设置销售员的职位
    this->salary_ = pay(); // 计算销售员的工资
    department_map[department] += sales; // 更新销售部门的销售额
}

double Salesman::pay() const
{
    return sales_ * 0.04; // 根据销售额计算销售员的工资
}

void Salesman::display() const
{
    DisplayEmployee(*this); // 显示销售员的基本信息
    cout << "Department:" << department_ << endl; // 显示销售员所属的部门
    cout << "Sales:" << sales_ << endl; // 显示销售员的销售额
}

void Salesman::promote(double salary) const
{
    // 销售员职位晋升逻辑，此处为空实现
}
