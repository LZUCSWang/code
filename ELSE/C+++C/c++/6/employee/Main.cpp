
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\6\employee\Main.cpp
 * @Description:某小型公司有四类人员：总经理、技术人员、销售经理、推销员。设计一个基类employee，
派生出manager（总经理）、technician（技术人员）、salesmanager（销售经理）、saleman（推销员）。销售经理既是经理又是销售人员，兼具两类人员的特点，因此同时继承manager 和salesman 两个类。
 */

// g++ -std=c++11 -o Main Main.cpp employee.cpp Date.cpp
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include "employee.h"
#include "Date.h"
using namespace std;

map<string, int> department_map; // 存储部门销售额的映射

// manager 类
class manager : virtual public employee
{
public:
    manager() {}
    manager(int id, const string &name, string gender, const Date &birth) : employee(id, name, gender, birth, "Manager", GetMonthlySalary()) {}
    double GetMonthlySalary() const override
    {
        return 8000.0; // 经理的月薪固定为8000元
    }
};

// technician 类
class technician : public employee
{
public:
    technician() {}
    technician(int id, const string &name, string gender, const Date &birth, double work_time) : work_time_(work_time)
    {
        this->id_ = id;
        this->name_ = name;
        this->gender_ = gender;
        this->birth_ = birth;
        this->position_ = "technician";
        this->salary_ = GetMonthlySalary();
    }
    double GetMonthlySalary() const override
    {
        return work_time_ * hourly_wage_; // 技术员的月薪为工作时间乘以时薪
    }

private:
    double hourly_wage_ = 25; // 技术员的时薪为25元
    double work_time_; // 工作时间
};

// salesman 类
class salesman : virtual public employee
{
public:
    salesman() {}
    salesman(int id, const string &name, string gender, const Date &birth, const string &department, double sales) : department_(department), sales_(sales)
    {
        this->id_ = id;
        this->name_ = name;
        this->gender_ = gender;
        this->birth_ = birth;
        this->position_ = "salesman";
        this->salary_ = GetMonthlySalary();
        department_map[department] += sales; // 将销售额累加到对应部门的销售额中
    }
    double GetMonthlySalary() const override
    {
        return sales_ * 0.04; // 销售员的月薪为销售额的4%
    }

protected:
    string department_; // 部门
    double sales_; // 销售额
};

// salesmanager 类
class salesmanager : public manager, public salesman
{
public:
    salesmanager() {}
    salesmanager(int id, const string &name, string gender, const Date &birth, const string &department)
    {
        this->id_ = id;
        this->name_ = name;
        this->birth_ = birth;
        this->gender_ = gender;
        this->department_ = department;
        this->position_ = "salesmanager";
        this->salary_ = GetMonthlySalary();
    }
    double GetMonthlySalary() const override
    {
        return 5000 + department_map[department_] * 0.05; // 销售经理的月薪为5000元加上部门销售额的5%
    }
};

int main()
{
    vector<employee *> employees; // 员工指针的向量
    int choice, year, month, day, work_time, sales;
    int id;
    string name;
    string gender;
    string department, position;

    while (true)
    {
        // 显示菜单选项
        cout << "1.添加经理" << endl
             << "2.添加技术员" << endl
             << "3.添加销售员" << endl
             << "4.添加销售经理" << endl
             << "5.显示所有员工" << endl
             << "6.退出" << endl;

        cin >> choice; // 获取用户选择

        switch (choice)
        {
        case 1:
            cout << "添加经理（id、姓名、性别、出生年份、月份、日期）" << endl;
            cin >> id >> name >> gender >> year >> month >> day;
            employees.push_back(new manager(id, name, gender, Date(year, month, day))); // 创建并添加经理对象到员工指针向量中
            break;
        case 2:
            cout << "添加技术员（id、姓名、性别、出生年份、月份、日期、工作时间）" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> work_time;
            employees.push_back(new technician(id, name, gender, Date(year, month, day), work_time)); // 创建并添加技术员对象到员工指针向量中
            break;
        case 3:
            cout << "添加销售员（id、姓名、性别、出生年份、月份、日期、部门、销售额）" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> department >> sales;
            employees.push_back(new salesman(id, name, gender, Date(year, month, day), department, sales)); // 创建并添加销售员对象到员工指针向量中
            break;
        case 4:
            cout << "添加销售经理（id、姓名、性别、出生年份、月份、日期、部门）" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> department;
            employees.push_back(new salesmanager(id, name, gender, Date(year, month, day), department)); // 创建并添加销售经理对象到员工指针向量中
            break;
        case 5:
            for (int i = 0; i < employees.size(); i++)
            {
                DisplayEmployee(*employees[i]); // 显示所有员工信息
            }
            cout << "=====================================" << endl;
            break;
        case 6:
            exit(0); // 退出程序
            break;
        default:
            cout << "输入错误！" << endl;
            break;
        }
    }

    system("pause");
    return 0;
}
