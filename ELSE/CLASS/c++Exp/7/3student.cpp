/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\7\3student.cpp
 * @Description: 学生成绩管理程序
 */
#include <iostream>
#include <cstring>
using namespace std;

const int N = 5; // 学生人数
const int M = 3; // 课程数

class Student
{
private:
    char name[10];        // 姓名
    int deg1, deg2, deg3; // 三门课的成绩

public:
    // 默认构造函数，将成绩初始化为0
    Student()
    {
        deg1 = deg2 = deg3 = 0;
    }

    // 带参构造函数，初始化姓名和三门课的成绩
    /**
     * @description: 带参构造函数，用于初始化学生对象的姓名和三门课的成绩
     * @param {char} na 姓名
     * @param {int} d1 语文成绩
     * @param {int} d2 英语成绩
     * @param {int} d3 数学成绩
     * @return {*}
     */
    Student(char na[], int d1, int d2, int d3)
    {
        strcpy(name, na);
        deg1 = d1;
        deg2 = d2;
        deg3 = d3;
    }

    // 运算符重载函数，实现学生成绩的累加
    /**
     * @description: 运算符重载函数，用于将两个学生对象的成绩进行累加
     * @param {Student} s1 第一个学生对象
     * @param {Student} s2 第二个学生对象
     * @return {Student} 返回累加后的学生对象
     */
    friend Student operator+(const Student &s1, const Student &s2)
    {
        Student s;
        strcpy(s.name, "AVG");
        s.deg1 = s1.deg1 + s2.deg1;
        s.deg2 = s1.deg2 + s2.deg2;
        s.deg3 = s1.deg3 + s2.deg3;
        return s;
    }

    // 全局函数，计算并输出平均成绩
    /**
     * @description: 计算并输出学生对象的平均成绩
     * @param {Student} &s 学生对象的引用
     * @param {int} n 学生人数
     * @return {*}
     */
    friend void avg(Student &s, int n)
    {
        cout << s.name << "\t\t  ";
        cout << s.deg1 / n << "\t    " << s.deg2 / n << "\t\t" << s.deg3 / n << endl;
        cout << "----------------------------------------------" << endl;
    }
};

int main()
{
    // 声明5个学生对象
    Student stu[N];

    // 输入学生信息和成绩
    for (int i = 0; i < N; i++)
    {
        char name[10];
        int d1, d2, d3;
        cout << "Please enter the first" << i + 1 << "Names of individual students and grades in three courses:";
        cin >> name >> d1 >> d2 >> d3;
        stu[i] = Student(name, d1, d2, d3);
    }

    // 计算班级平均成绩
    cout << "----------------------------------------------" << endl;
    cout << "Student's name \t Language  English  Mathematics" << endl;
    cout << "----------------------------------------------" << endl;
    Student avg_deg = Student("Average", 0, 0, 0); // 定义一个学生对象，用于存放班级平均成绩
    for (int i = 0; i < N; i++)
    {
        avg_deg = avg_deg + stu[i];
        avg(stu[i], 1);
    }
    avg(avg_deg, N);
    return 0;
}
