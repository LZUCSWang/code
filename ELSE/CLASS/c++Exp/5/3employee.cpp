<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\5\3employee.cpp
 * @Description: 设计某小型公司的 employee（人员）类
1、类
1）employee 类：
基本信息：编号、姓名、性别、出生日期、职位等；
出生日期使用自定义的 Date（日期）类；
其中：基本信息为 private 属性，成员函数为public 属性；
多个构造函数：缺省构造函数、带参数的构造函数、带默认参数的构造函数；可以从外部访问类成员的友员函数；
2）Date 类：
成员变量：年、月、日
成员函数：SetYear(int year)、SetMonth(int month)、SetDay(int day)
GetYear()、GetMonth()、GetDay()
2、基本功能：
1）职工信息的录入；
2）职工信息的显示；
3）用对象数组保存已输入的职工对象；
4）可以修改人员的基本信息，如：姓名、职位等；
5）可以通过编号或姓名进行人员查询；

 */

=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
#include <iostream>
#include <string>

using namespace std;

class Date
{
private:
<<<<<<< HEAD
    int year;  // 年份
    int month; // 月份
    int day;   // 日期
=======
    int year;
    int month;
    int day;
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e

public:
    void SetYear(int year)
    {
        this->year = year;
    }
    void SetMonth(int month)
    {
        this->month = month;
    }
    void SetDay(int day)
    {
        this->day = day;
    }
    int GetYear()
    {
        return year;
    }
    int GetMonth()
    {
        return month;
    }
    int GetDay()
    {
        return day;
    }
};

class Employee
{
private:
<<<<<<< HEAD
    int number;      // 员工编号
    string name;     // 员工姓名
    string sex;      // 员工性别
    Date birth;      // 员工出生日期
    string position; // 员工职位

public:
    Employee() {} // 默认构造函数

    // 带参数的构造函数，用于初始化员工信息
=======
    int number;
    string name;
    string sex;
    Date birth;
    string position;

public:
    Employee() {}
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    Employee(int num, string n, string s, int y, int m, int d, string pos)
    {
        number = num;
        name = n;
        sex = s;
        birth.SetYear(y);
        birth.SetMonth(m);
        birth.SetDay(d);
        position = pos;
    }
<<<<<<< HEAD

    // 带参数的构造函数，用于初始化员工信息（不包含性别和出生日期）
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    Employee(int num, string n, string pos)
    {
        number = num;
        name = n;
        position = pos;
    }
<<<<<<< HEAD

    // 修改员工信息
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    void ModifyInfo(string n, string pos)
    {
        name = n;
        position = pos;
    }
<<<<<<< HEAD

    // 显示员工信息
    void DisplayInfo()
    {
        cout << "====================" << endl;
        cout << "Employee Number: " << number << endl;
        cout << "Employee Name: " << name << endl;
        cout << "Employee Gender: " << sex << endl;
        cout << "Employee Date of Birth: " << birth.GetYear() << " / " << birth.GetMonth() << " / " << birth.GetDay() << endl;
        cout << "Employee Position: " << position << endl;
    }

    friend void SearchByNumber(Employee *empList, int n, int num);
    friend void SearchByName(Employee *empList, int n, string name);

=======
    void DisplayInfo()
    {
        cout << "员工编号：" << number << endl;
        cout << "员工姓名：" << name << endl;
        cout << "员工性别：" << sex << endl;
        cout << "员工出生日期：" << birth.GetYear() << "年" << birth.GetMonth() << "月" << birth.GetDay() << "日" << endl;
        cout << "员工职位：" << position << endl;
    }
    friend void SearchByNumber(Employee *empList, int n, int num);
    friend void SearchByName(Employee *empList, int n, string name);
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    int getNumber()
    {
        return number;
    }
};

<<<<<<< HEAD
/**
 * @description: 友元函数，类外实现，按员工编号查找员工
 * @param {Employee} *empList   职工类指针，指向职工类数组
 * @param {int} n               职工类数组长度
 * @param {int} num             职工编号
 * @return {*}
 */
=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void SearchByNumber(Employee *empList, int n, int num)
{
    for (int i = 0; i < n; i++)
    {
        if (empList[i].number == num)
        {
            empList[i].DisplayInfo();
            return;
        }
    }
<<<<<<< HEAD
    cout << "Employee with number " << num << " not found!" << endl;
}

/**
 * @description: 友元函数，类外实现，按员工姓名查找员工
 * @param {Employee} *empList   职工类指针，指向职工类数组
 * @param {int} n               职工类数组长度
 * @param {string} name         职工编号
 * @return {*}
 */
=======
    cout << "未找到编号为" << num << "的员工！" << endl;
}

>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
void SearchByName(Employee *empList, int n, string name)
{
    for (int i = 0; i < n; i++)
    {
        if (empList[i].name == name)
        {
            empList[i].DisplayInfo();
            return;
        }
    }
<<<<<<< HEAD
    cout << "Employee with name " << name << " not found!" << endl;
=======
    cout << "未找到姓名为" << name << "的员工！" << endl;
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
}

int main()
{
    Employee empList[4];
    int n = 4;
    int choice = 0;
    int num;
    string name, s;
    int y, m, d;
    string pos;
    while (choice != 6)
    {
<<<<<<< HEAD
        cout << "Select an option:\n1. Enter employee information\n2. Display employee information\n3. Modify employee information\n4. Search by employee number\n5. Search by employee name\n6. Exit\n";
=======
        cout << "请选择操作：\n1. 录入职工信息\n2. 显示职工信息\n3. 修改职工信息\n4. 按编号查询\n5. 按姓名查询\n6. 退出\n";
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
        cin >> choice;
        switch (choice)
        {
        case 1:
            for (int i = 0; i < n; i++)
            {
<<<<<<< HEAD
                cout << "Enter employee " << i + 1 << "'s information:" << endl;
                cout << "Enter employee number: ";
                cin >> num;
                cout << "Enter employee name: ";
                cin >> name;
                cout << "Enter employee gender: ";
                cin >> s;
                cout << "Enter employee birth year: ";
                cin >> y;
                cout << "Enter employee birth month: ";
                cin >> m;
                cout << "Enter employee birth day: ";
                cin >> d;
                cout << "Enter employee position: ";
=======
                cout << "请输入职工编号：";
                cin >> num;
                cout << "请输入职工姓名：";
                cin >> name;
                cout << "请输入职工性别：";
                cin >> s;
                cout << "请输入职工出生年份：";
                cin >> y;
                cout << "请输入职工出生月份：";
                cin >> m;
                cout << "请输入职工出生日期：";
                cin >> d;
                cout << "请输入职工职位：";
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
                cin >> pos;
                empList[i] = Employee(num, name, s, y, m, d, pos);
            }
            break;
        case 2:
            for (int i = 0; i < n; i++)
            {
                empList[i].DisplayInfo();
            }
            break;
        case 3:
<<<<<<< HEAD
            cout << "Enter the employee number to modify: ";
            cin >> num;
            cout << "Enter the new employee name: ";
            cin >> name;
            cout << "Enter the new employee position: ";
=======
            cout << "请输入要修改的职工编号：";
            cin >> num;
            cout << "请输入新的职工姓名：";
            cin >> name;
            cout << "请输入新的职工职位：";
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
            cin >> pos;
            for (int i = 0; i < n; i++)
            {
                if (empList[i].getNumber() == num)
                {
                    empList[i].ModifyInfo(name, pos);
                    break;
                }
            }
            break;
        case 4:
<<<<<<< HEAD
            cout << "Enter the employee number to search: ";
=======
            cout << "请输入要查询的职工编号：";
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
            cin >> num;
            SearchByNumber(empList, n, num);
            break;
        case 5:
<<<<<<< HEAD
            cout << "Enter the employee name to search: ";
=======
            cout << "请输入要查询的职工姓名：";
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
            cin >> name;
            SearchByName(empList, n, name);
            break;
        case 6:
<<<<<<< HEAD
            cout << "Program ended!" << endl;
            break;
        default:
            cout << "Invalid input!" << endl;
            break;
        }
    }
    return 0;
}
=======
            cout << "程序结束！" << endl;
            break;
        default:
            cout << "输入错误！" << endl;
            break;
        }
    }
}
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
