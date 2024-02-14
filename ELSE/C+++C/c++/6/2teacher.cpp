#include <iostream>
#include <string>
using namespace std;

class Teacher
{
protected:
    string name;     // 姓名
    int age;         // 年龄
    string gender;   // 性别
    string address;  // 地址
    string phone;    // 手机号
    string title;    // 职称

public:
    Teacher() {} // 默认构造函数
    Teacher(string n, int a, string g, string add, string p, string t)
        : name(n), age(a), gender(g), address(add), phone(p), title(t)
    {
    }

    void display() // 显示教师信息
    {
        cout << "Name:" << name << endl;     // 输出姓名
        cout << "Age:" << age << endl;       // 输出年龄
        cout << "Gender:" << gender << endl; // 输出性别
        cout << "Address:" << address << endl;   // 输出地址
        cout << "Phone:" << phone << endl;   // 输出手机号
        cout << "Title:" << title << endl;   // 输出职称
    }
};

class Cadre
{
protected:
    string name;     // 姓名
    int age;         // 年龄
    string gender;   // 性别
    string address;  // 地址
    string phone;    // 手机号
    string post;     // 岗位

public:
    Cadre() {} // 默认构造函数
    Cadre(string n, int a, string g, string add, string p, string post)
        : name(n), age(a), gender(g), address(add), phone(p), post(post)
    {
    }

    void display() // 显示干部信息
    {
        cout << "Name:" << name << endl;     // 输出姓名
        cout << "Age:" << age << endl;       // 输出年龄
        cout << "Gender:" << gender << endl; // 输出性别
        cout << "Address:" << address << endl;   // 输出地址
        cout << "Phone:" << phone << endl;   // 输出手机号
        cout << "岗位:" << post << endl;        // 输出岗位
    }
};

class Teacher_Cadre : public Teacher, public Cadre
{
protected:
    int wages; // 工资

public:
    Teacher_Cadre() {} // 默认构造函数
    Teacher_Cadre(string n, int a, string g, string add, string p, string t, string post, int w)
        : Teacher(n, a, g, add, p, t), Cadre(n, a, g, add, p, post), wages(w)
    {
    }

    void Show() // 显示教师兼干部的信息
    {
        Teacher::display();                 // 调用Teacher类的display函数，显示教师信息
        cout << "Wages:" << wages << endl;   // 输出工资
    }
};

int main()
{
    Teacher_Cadre tc[20]; // 声明一个Teacher_Cadre类型的数组，用于存储教师兼干部的信息
    int choice;          // 用户选择
    string n, g, add, p, t, post; // 临时变量，用于存储输入的姓名、性别、地址、手机号、职称、岗位
    int a, w;            // 临时变量，用于存储输入的年龄、工资
    int index = 0;       // 数组索引，表示当前已经存储的教师兼干部的数量

    while (true)
    {
        cout << "1.Add\n2.show\n3.exit" << endl;  // 显示菜单选项
        cin >> choice;                             // 获取用户选择
        getchar();                                 // 处理换行符

        switch (choice)
        {
        case 1:
            cout << "Add NO." << index + 1 << " info" << endl;  // 输入要添加的教师兼干部信息编号
            cout << "Input Name:";                             // 输入姓名
            getline(cin, n);
            cout << "Input Age:";                              // 输入年龄
            cin >> a;
            getchar();
            cout << "Input gender:";                           // 输入性别
            getline(cin, g);
            cout << "Input address:";                          // 输入地址
            getline(cin, add);
            cout << "Input phone:";                            // 输入手机号
            getline(cin, p);
            cout << "Input title:";                            // 输入职称
            getline(cin, t);
            cout << "Input post:";                             // 输入岗位
            getline(cin, post);
            cout << "Input wages:";                            // 输入工资
            cin >> w;
            tc[index++] = Teacher_Cadre(n, a, g, add, p, t, post, w); // 在数组中添加教师兼干部信息
            break;

        case 2:
            for (int i = 0; i < index; i++)
            {
                cout << "No." << i + 1 << " info" << endl; // 显示第i个教师兼干部的信息
                tc[i].Show();
            }
            break;

        case 3:
            return 0;

        default:
            break;
        }
    }

    return 0;
}
