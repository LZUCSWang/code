/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\8\employee\Main.cpp
 * @Description: 员工管理系统主程序
 */

// g++ -std=c++11 -o Main Main.cpp employee.cpp Date.cpp manager.cpp technician.cpp salesman.cpp salesmanager.cpp
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include "Employee.h"
#include "Date.h"
#include "Manager.h"
#include "Salesman.h"
#include "Salesmanager.h"
#include "Technician.h"
using namespace std;

map<string, int> department_map; // 部门映射表，用于存储部门名称和编号的映射关系

int main()
{
    vector<Employee *> employees; // 存储所有员工的指针数组，数组中的每个元素都是一个指向Employee对象的指针，这样做的目的是为了实现多态

    int choice, year, month, day, work_time, sales;
    int id;
    string name;
    char gender;
    string department, position;

    while (true)
    {
        // 显示菜单选项
        cout << "1.add Manager" << endl
             << "2.add Technician" << endl
             << "3.add Salesman" << endl
             << "4.add Salesmanager" << endl
             << "5.show all employees" << endl
             << "6.exit" << endl;

        cin >> choice; // 输入选项

        switch (choice)
        {
        case 1:
            cout << "Adding a Manager(id,name,gender,year,month,day)" << endl;
            cin >> id >> name >> gender >> year >> month >> day;

            // 创建Manager对象并添加到employees数组中
            employees.push_back(new Manager(id, name, gender, Date(year, month, day)));
            break;
        case 2:
            cout << "Adding a Technician(id,name,gender,year,month,day,work_time)" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> work_time;

            // 创建Technician对象并添加到employees数组中
            employees.push_back(new Technician(id, name, gender, Date(year, month, day), work_time));
            break;
        case 3:
            cout << "Adding a Salesman(id,name,gender,year,month,day,department,sales)" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> department >> sales;

            // 创建Salesman对象并添加到employees数组中
            employees.push_back(new Salesman(id, name, gender, Date(year, month, day), department, sales));
            break;
        case 4:
            cout << "Adding a Salesmanager(id,name,gender,year,month,day,department)" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> department;

            // 创建Salesmanager对象并添加到employees数组中
            employees.push_back(new Salesmanager(id, name, gender, Date(year, month, day), department));
            break;
        case 5:
            // 显示所有员工信息
            for (int i = 0; i < employees.size(); i++)
            {
                employees[i]->display();
            }
            cout << "=====================================" << endl;
            break;
        case 6:
            exit(0); // 退出程序
            break;
        default:
            cout << "input error!" << endl; // 输入错误处理
            break;
        }
    }

    system("pause");
    return 0;
}
