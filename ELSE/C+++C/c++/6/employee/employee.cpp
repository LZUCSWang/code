/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\6\employee\employee.cpp
 * @Description: employee类的实现文件，包含友元函数DisplayEmployee的实现
 */

#include "employee.h"
using namespace std;

// 参数化构造函数的定义
employee::employee(int id, const string &name, string gender, const Date &birth, const string &position, double salary)
    : id_(id), name_(name), gender_(gender), birth_(birth), position_(position), salary_(salary) {}

// 友元函数用于显示员工信息的定义
void DisplayEmployee(const employee &e)
{
    cout << "==============================" << endl;
    cout << "ID:" << e.id_ << endl;
    cout << "Name: " << e.name_ << endl;
    cout << "Gender: " << e.gender_ << endl;
    cout << "Birthday: " << e.birth_.GetYear() << "." << e.birth_.GetMonth() << "." << e.birth_.GetDay() << endl;
    cout << "Position: " << e.position_ << endl;
    cout << "Salary: " << e.salary_ << endl;
}
