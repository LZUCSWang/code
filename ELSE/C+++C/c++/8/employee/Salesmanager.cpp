/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Salesmanager.cpp
 * @Description: 销售经理类实现文件
 */

#include "Salesmanager.h"
extern map<string, double> department_map;

// Salesmanager 类
Salesmanager::Salesmanager(int id, const string &name, char gender, const Date &birth, const string &department)
{
    this->id_ = id; // 设置销售经理的ID
    this->name_ = name; // 设置销售经理的姓名
    this->birth_ = birth; // 设置销售经理的出生日期
    this->gender_ = gender; // 设置销售经理的性别
    this->department_ = department; // 设置销售经理的部门
    this->position_ = "Salesmanager"; // 设置销售经理的职位
    this->salary_ = pay(); // 计算销售经理的工资
}

double Salesmanager::pay() const
{
    return 5000 + department_map[department_] * 0.05; // 根据部门的销售额计算销售经理的工资
}

void Salesmanager::display() const
{
    DisplayEmployee(*this); // 显示销售经理的基本信息
    cout << "Department:" << department_ << endl; // 显示销售经理所属的部门
}

void Salesmanager::promote(double salary) const
{
    // 销售经理职位晋升逻辑，此处为空实现
}
