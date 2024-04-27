/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\employee.cpp
 * @Description: 员工类实现文件
 */

#include "Employee.h"
using namespace std;

// 构造函数，初始化员工信息
Employee::Employee(int id, const string &name, char gender, const Date &birth, const string &position, double salary)
    : id_(id), name_(name), gender_(gender), birth_(birth), position_(position), salary_(salary)
{
}

// 友元函数，用于显示员工信息
void DisplayEmployee(const Employee &e)
{
    cout << "==============================" << endl;
    cout << "ID:" << e.id_ << endl;
    cout << "Name:" << e.name_ << endl;
    cout << "Gender:" << e.gender_ << endl;
    cout << "Birthday:" << e.birth_.GetYear() << "." << e.birth_.GetMonth() << "." << e.birth_.GetDay() << endl;
    cout << "Position:" << e.position_ << endl;
    cout << "Salary:" << e.salary_ << endl;
}
