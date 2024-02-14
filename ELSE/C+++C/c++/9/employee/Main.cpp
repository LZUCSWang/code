/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\9\employee\Main.cpp
 * @Description:
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

// 部门销售额统计
map<string, int> department_map;  // 使用map容器存储部门和对应的销售额

// manager 类
class manager : virtual public employee
{
public:
    manager() {}
    manager(int id, const string &name, char gender, const Date &birth) : employee(id, name, gender, birth, "Manager", GetMonthlySalary()) {}
    /**
     * @description: 显示经理的信息
     * @param {ostream} &fout 输出流对象
     * @return {*}
     */
    void Display(ostream &fout) override
    {
        DisplayEmployee(*this, fout);  // 调用DisplayEmployee函数显示经理的基本信息
    }
    /**
     * @description: 获取经理的月薪
     * @return {double} 经理的月薪
     */
    double GetMonthlySalary() const override
    {
        return 8000.0;  // 固定月薪为8000.0元
    }
};
// technician 类
class technician : public employee
{
public:
    technician() {}
    technician(int id, const string &name, char gender, const Date &birth, double work_time) : work_time_(work_time)
    {
        this->id_ = id;
        this->name_ = name;
        this->gender_ = gender;
        this->birth_ = birth;
        this->position_ = "technician";
        this->salary_ = GetMonthlySalary();
    }
    void Display(ostream &fout) override // 重写虚函数,添加工作时间的输出
    {
        DisplayEmployee(*this, fout);
        fout << "Work time:" << work_time_ << endl;
    }
    double GetMonthlySalary() const override
    {
        return work_time_ * 25;
    }

private:
    double work_time_;
};
// salesman 类
class salesman : virtual public employee
{
public:
    salesman() {}
    salesman(int id, const string &name, char gender, const Date &birth, const string &department, double sales) : department_(department), sales_(sales)
    {
        this->id_ = id;
        this->name_ = name;
        this->gender_ = gender;
        this->birth_ = birth;
        this->position_ = "salesman";
        this->salary_ = GetMonthlySalary();
        department_map[department] += sales;
    }
    void Display(ostream &fout) override
    {
        DisplayEmployee(*this, fout);
        fout << "Department:" << department_ << endl;
        fout << "Sales:" << sales_ << endl;
    }
    double GetMonthlySalary() const override
    {
        return sales_ * 0.04;
    }

protected:
    string department_;
    double sales_;
};
// salesmanager 类
class salesmanager : public manager, public salesman
{
public:
    salesmanager() {}
    salesmanager(int id, const string &name, char gender, const Date &birth, const string &department)
    {
        this->id_ = id;
        this->name_ = name;
        this->birth_ = birth;
        this->gender_ = gender;
        this->department_ = department;
        this->position_ = "salesmanager";
        this->salary_ = GetMonthlySalary();
    }
    void Display(ostream &fout) override
    {
        DisplayEmployee(*this, fout);
        fout << "Department:" << department_ << endl;
        fout << "Sales:" << department_map[department_] << endl;
    }
    double GetMonthlySalary() const override
    {
        return 5000 + department_map[department_] * 0.05;
    }
};
/**
 * @description: 将员工信息保存到文件中
 * @param {vector<employee *>} &employees 员工向量的引用，包含要保存的员工信息
 * @return {*}
 */
void SaveToFile(vector<employee *> &employees)
{
    ofstream fout(".\\employee.txt");          // 打开名为"employee.txt"的文件进行写入
    for (int i = 0; i < employees.size(); i++) // 遍历employees向量中的每个员工
    {
        employees[i]->Display(fout); // 调用员工对象的Display方法，将员工信息写入文件
        fout << "#" << endl;         // 输出"#"表示一条员工信息的结束
    }
}

/**
 * @description: 从文件中加载员工信息并存储到员工向量中
 * @param {vector<employee *>} &employees 员工向量的引用，用于存储加载的员工信息
 * @return {*}
 */
void LoadFromFile(vector<employee *> &employees)
{
    ifstream fin(".\\employee.txt"); // 打开名为"employee.txt"的文件进行读取
    if (!fin.is_open())              // 如果文件打开失败，则输出错误信息并退出
    {
        cout << "Open file failed!" << endl;
        return;
    }
    string line;                                        // 用于存储读取的每一行内容
    int id, year, month, day, salary, work_time, sales; // 员工信息的各个字段
    string name, position, department;                  // 员工信息的各个字段
    char gender;                                        // 员工信息的各个字段

    // 逐行读取文件内容
    while (getline(fin, line))
    {
        // cout << line << endl;
        if (line.find("#") == 0) // 如果行以"#"开头，则表示员工信息的一条记录结束
        {
            if (position == "Manager") // 如果职位为Manager
            {
                employees.push_back(new manager(id, name, gender, Date(year, month, day))); // 创建Manager对象并添加到employees向量中
            }
            else if (position == "technician") // 如果职位为technician
            {
                employees.push_back(new technician(id, name, gender, Date(year, month, day), salary)); // 创建technician对象并添加到employees向量中
            }
            else if (position == "salesman") // 如果职位为salesman
            {
                employees.push_back(new salesman(id, name, gender, Date(year, month, day), department, salary)); // 创建salesman对象并添加到employees向量中
            }
            else if (position == "salesmanager") // 如果职位为salesmanager
            {
                employees.push_back(new salesmanager(id, name, gender, Date(year, month, day), department)); // 创建salesmanager对象并添加到employees向量中
            }
        }
        else if (line.find("ID") == 0) // 如果行以"ID"开头，则表示当前行为员工的ID信息
        {
            id = stoi(line.substr(3)); // 提取行中的数字部分，将其转换为整数，赋值给变量id
        }
        else if (line.find("Name") == 0) // 如果行以"Name"开头，则表示当前行为员工的姓名信息
        {
            name = line.substr(5); // 提取行中的姓名部分，赋值给变量name
        }
        else if (line.find("Gender") == 0) // 如果行以"Gender"开头，则表示当前行为员工的性别信息
        {
            gender = line[7]; // 提取行中的性别字符，赋值给变量gender
        }
        else if (line.find("Birthday") == 0) // 如果行以"Birthday"开头，则表示当前行为员工的出生日期信息
        {
            year = stoi(line.substr(9, 4));   // 提取行中的年份部分，转换为整数，赋值给变量year
            month = stoi(line.substr(14, 2)); // 提取行中的月份部分，转换为整数，赋值给变量month
            day = stoi(line.substr(17, 2));   // 提取行中的日期部分，转换为整数，赋值给变量day
        }
        else if (line.find("Position") == 0) // 如果行以"Position"开头，则表示当前行为员工的职位信息
        {
            position = line.substr(9); // 提取行中的职位部分，赋值给变量position
        }
        else if (line.find("Work time") == 0) // 如果行以"Work time"开头，则表示当前行为员工的工作时间信息
        {
            work_time = stoi(line.substr(10)); // 提取行中的数字部分，将其转换为整数，赋值给变量work_time
        }
        else if (line.find("Department") == 0) // 如果行以"Department"开头，则表示当前行为员工的部门信息
        {
            department = line.substr(11); // 提取行中的部门部分，赋值给变量department
        }
        else if (line.find("Sales") == 0) // 如果行以"Sales"开头，则表示当前行为销售员工的销售额信息
        {
            sales = stoi(line.substr(6)); // 提取行中的数字部分，将其转换为整数，赋值给变量sales
        }
        else if (line.find("Salary") == 0) // 如果行以"Salary"开头，则表示当前行为员工的薪水信息
        {
            salary = stoi(line.substr(7)); // 提取行中的数字部分，将其转换为整数，赋值给变量salary
        }
    }
}

int main()
{
    vector<employee *> employees;                   // 存放所有员工的指针
    int choice, year, month, day, work_time, sales; // 选择，年，月，日，工作时间，销售额
    int id;                                         // 员工编号
    string name;                                    // 员工姓名
    char gender;
    string department, position;
    while (true)
    {
        cout << "=====================================" << endl
             << "1.add manager" << endl
             << "2.add technician" << endl
             << "3.add salesman" << endl
             << "4.add salesmanager" << endl
             << "5.show all employees" << endl
             << "6.save to file" << endl
             << "7.load from file" << endl
             << "8.exit" << endl;
        cin >> choice; // 选择
        switch (choice)
        {
        case 1:
            cout << "Adding a manager(id,name,gender,year,month,day)" << endl;
            cin >> id >> name >> gender >> year >> month >> day;
            employees.push_back(new manager(id, name, gender, Date(year, month, day))); // 添加一个manager对象
            break;
        case 2:
            cout << "Adding a technician(id,name,gender,year,month,day,work_time)" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> work_time;
            employees.push_back(new technician(id, name, gender, Date(year, month, day), work_time));
            break;
        case 3:
            cout << "Adding a salesman(id,name,gender,year,month,day,department,sales)" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> department >> sales;
            employees.push_back(new salesman(id, name, gender, Date(year, month, day), department, sales));
            break;
        case 4:
            cout << "Adding a salesmanager(id,name,gender,year,month,day,department)" << endl;
            cin >> id >> name >> gender >> year >> month >> day >> department;
            employees.push_back(new salesmanager(id, name, gender, Date(year, month, day), department));
            break;
        case 5:
            cout << employees.size() << endl;
            for (int i = 0; i < employees.size(); i++)
            {
                employees[i]->Display(cout);
            }
            cout << "=====================================" << endl;
            break;
        case 6:
            SaveToFile(employees);
            break;
        case 7:
            LoadFromFile(employees);
            break;
        case 8:
            for (int i = 0; i < employees.size(); i++)
            {
                delete employees[i];
            }
            employees.clear();
            exit(0);
        default:
            cout << "Input error!" << endl;
            break;
        }
    }
    system("pause");
    return 0;
}