#include <bits/stdc++.h>
using namespace std;
#define MAX 10000

class student
{
// void conFun() const;常函数 不能修改成员变量，用于修饰this指针
public:
    student(int num, string name) : id(num) {}
    int get_id()
    {
        return id;
    }

private:
    const int id;
    string name;
};

int main()
{
    student stu1(1001, "Bob");
    const student stu2(1002, "Alice");
    cout << stu1.get_id() << endl;
    cout << stu2.get_id() << endl;
    return 0;
}