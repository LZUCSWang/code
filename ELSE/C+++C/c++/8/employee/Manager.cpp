/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Manager.cpp
 * @Description: 管理人员类实现文件
 */

#include "Manager.h"

// Manager 类

// Manager() {}
Manager::Manager(int id, const string &name, char gender, const Date &birth) : Employee(id, name, gender, birth, "Manager", pay()) {}
// 构造函数，调用基类 Employee 的构造函数进行初始化，并指定职位为 Manager，工资通过调用 pay() 函数计算得到

double Manager::pay() const 
{
    return 8000.0; // 返回固定工资 8000.0
}

void Manager::display() const 
{
    DisplayEmployee(*this); // 调用全局函数 DisplayEmployee() 显示员工信息
}

void Manager::promote(double salary) const 
{
    // 空函数体，Manager 类没有实现提升薪水的功能
}
