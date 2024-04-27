/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\5\2studentPlus.cpp
 * @Description: 
 */
#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string id;        // 学生ID
    string name;      // 学生姓名
    string gender;    // 学生性别
    string birthdate; // 学生出生日期
    string grade;     // 学生年级
    string cls;       // 学生班级
    string dept;      // 学生所在系别
    string major;     // 学生专业
    static int count; // 当前已创建的学生数量

public:
    Student()
    {
        count++;                // 每创建一个学生对象，数量加一
        id = "S" + to_string(count); // 设置学号为"S" + 学生数量
    }

    // 构造函数，用于初始化学生对象的各个属性
    Student(string name, string gender, string birthdate,
            string grade, string cls, string dept, string major)
        : name(name), gender(gender), birthdate(birthdate),
          grade(grade), cls(cls), dept(dept), major(major)
    {
        count++;                // 每创建一个学生对象，数量加一
        id = "S" + to_string(count); // 设置学号为"S" + 学生数量
    }

    // 显示学生信息的方法
    void show()
    {
        cout << "ID:\t\t" << id << endl;             // 输出学生ID
        cout << "Name:\t\t" << name << endl;         // 输出学生姓名
        cout << "Gender:\t\t" << gender << endl;     // 输出学生性别
        cout << "Birthdate:\t" << birthdate << endl; // 输出学生出生日期
        cout << "Grade:\t\t" << grade << endl;       // 输出学生年级
        cout << "Cls:\t\t" << cls << endl;           // 输出学生班级
        cout << "Dept:\t\t" << dept << endl;         // 输出学生所在系别
        cout << "Major:\t\t" << major << endl;       // 输出学生专业
    }
};

int Student::count = 0; // 静态成员变量初始化为0

int main()
{
    Student students[5]; // 创建一个包含5个学生对象的数组

    for (int i = 0; i < 5; i++)
    {
        cout << "Input NO." << i + 1 << " Student's info " << endl;
        string name, gender, birthdate, grade, cls, dept, major;

        cout << "Input Name:\t\t";
        getline(cin, name); // 获取学生姓名

        cout << "Input Gender:\t\t";
        getline(cin, gender); // 获取学生性别

        cout << "Input Birthdate:\t";
        getline(cin, birthdate); // 获取学生出生日期

        cout << "Input Grade:\t\t";
        getline(cin, grade); // 获取学生年级

        cout << "Input Cls:\t\t";
        getline(cin, cls); // 获取学生班级

        cout << "Input Dept:\t\t";
        getline(cin, dept); // 获取学生所在系别

        cout << "Input Major:\t\t";
        getline(cin, major); // 获取学生专业

        students[i] = Student(name, gender, birthdate, grade, cls, dept, major); // 使用获取的信息创建学生对象并将其存储在数组中
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "Showing the NO." << i + 1 << " student's info" << endl;
        students[i].show(); // 显示学生信息
        cout << endl;
    }

    return 0;
}
