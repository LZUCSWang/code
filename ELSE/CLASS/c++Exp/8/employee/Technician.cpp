/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Technician.cpp
 * @Description: 技术人员类实现文件
 */

#include "Technician.h"
// Technician 类

// Technician() {}
Technician::Technician(int id, const string &name, char gender, const Date &birth, double work_time) : work_time_(work_time)
{
    this->id_ = id; // 设置技术人员的ID
    this->name_ = name; // 设置技术人员的姓名
    this->gender_ = gender; // 设置技术人员的性别
    this->birth_ = birth; // 设置技术人员的生日
    this->position_ = "Technician"; // 设置技术人员的职位为“Technician”
    this->salary_ = pay(); // 计算技术人员的工资
}

double Technician::pay() const
{
    return work_time_ * 25; // 技术人员的工资计算公式：工作时长 * 每小时工资
}

void Technician::display() const
{
    DisplayEmployee(*this); // 调用辅助函数显示技术人员信息
    cout << "Work time:" << work_time_ << endl; // 显示技术人员的工作时长
}

void Technician::promote(double salary) const {} // 技术人员职位晋升函数（不实现具体逻辑）
