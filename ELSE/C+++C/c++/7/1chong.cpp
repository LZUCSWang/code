/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\7\1chong.cpp
 * @Description: 设计字符串类String，用来存放不定长的字符串，重载运算符“= =”，“>”，“<”，用于两个字符串的大于、小于和等于的比较运算。
 */

#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
    char *str; // 存放字符串的字符数组

public:
    String() // 默认构造函数
    {
        str = new char[1]; // 动态分配一个字符大小的空间
        str[0] = '\0'; // 将字符串的第一个字符设置为结束符'\0'
    }

    String(const char *s) // 带参构造函数，用于接收一个C风格字符串
    {
        str = new char[strlen(s) + 1]; // 根据字符串长度动态分配内存空间
        strcpy(str, s); // 将传入的字符串复制到str中
    }

    String(const String &s) // 拷贝构造函数
    {
        str = new char[strlen(s.str) + 1]; // 根据传入字符串s的长度动态分配内存空间
        strcpy(str, s.str); // 将s.str复制到str中
    }

    ~String() // 析构函数，用于释放动态分配的内存空间
    {
        delete[] str; // 释放str指向的内存空间
    }

    String &operator=(const String &s) // 重载赋值运算符=
    {
        if (this == &s) // 检查是否为自我赋值
        {
            return *this; // 若是自我赋值，直接返回当前对象
        }
        delete[] str; // 释放当前对象的字符串内存空间
        str = new char[strlen(s.str) + 1]; // 根据传入字符串s的长度重新分配内存空间
        strcpy(str, s.str); // 将s.str复制到当前对象的字符串中
        return *this; // 返回当前对象
    }

    bool operator==(const String &s) const // 重载相等运算符==
    {
        return strcmp(str, s.str) == 0; // 比较两个字符串是否相等，使用strcmp函数
    }

    bool operator>(const String &s) const // 重载大于运算符>
    {
        return strcmp(str, s.str) > 0; // 比较当前字符串与传入字符串s的大小，使用strcmp函数
    }

    bool operator<(const String &s) const // 重载小于运算符<
    {
        return strcmp(str, s.str) < 0; // 比较当前字符串与传入字符串s的大小，使用strcmp函数
    }

    friend ostream &operator<<(ostream &os, const String &s) // 友元函数重载输出运算符<<
    {
        os << s.str; // 将字符串输出到流os中
        return os; // 返回流对象
    }
};

int main()
{
    String s1("China china"); // 创建String对象s1，并初始化为"China china"
    String s2("National Computer"); // 创建String对象s2，并初始化为"National Computer"
    String s3("Examination Rank"); // 创建String对象s3，并初始化为"Examination Rank"
    String s4("swust swust"); // 创建String对象s4，并初始化为"swust swust"

    cout << (s1 == s2) << endl; // 输出s1和s2的相等比较结果
    cout << (s1 > s2) << endl; // 输出s1和s2的大小比较结果
    cout << (s1 < s2) << endl; // 输出s1和s2的大小比较结果
    cout << (s1 == s1) << endl; // 输出s1和s1的相等比较结果
    cout << (s1 > s1) << endl; // 输出s1和s1的大小比较结果
    cout << (s1 < s1) << endl; // 输出s1和s1的大小比较结果

    system("pause"); // 暂停程序，等待用户按键关闭窗口
}