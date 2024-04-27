<<<<<<< HEAD
/*
 * @Author: 王贤义
 * @FilePath: \code\C+++C\c++\5\2student.cpp
 * @Description: 设计一个 Studnet(学生)类
1、基本信息：学号、姓名、性别、出生日期、年级、班级、院系、专业；
其中：基本信息为 private 属性，成员函数为public 属性；
2、Student 类有多个构造函数：缺省构造函数、带参数的构造函数、带默认参数的构造
函数
3、基本功能：
1）使用对象数组保存学生对象；
2）可以从键盘输入学生的基本信息；
3）SetInfo(形参表)函数可以修改学生的基本信息函数，例如：班级、专业等；
4）Show()函数显示学生信息；

 */

=======
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
<<<<<<< HEAD
    string id;        // 学生ID
    string name;      // 学生姓名
    string gender;    // 学生性别
    string birthdate; // 学生出生日期
    string grade;     // 学生年级
    string cls;       // 学生班级
    string dept;      // 学生所在系别
    string major;     // 学生专业

public:
    Student() {} // 默认构造函数

    // 构造函数，用于初始化学生对象的各个属性
=======
    string id;        // ѧ��
    string name;      // ����
    string gender;    // �Ա�
    string birthdate; // ��������
    string grade;     // �꼶
    string cls;       // �༶
    string dept;      // Ժϵ
    string major;     // רҵ

public:
    // ���캯��
    Student() {}
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    Student(string id, string name, string gender, string birthdate,
            string grade, string cls, string dept, string major)
        : id(id), name(name), gender(gender), birthdate(birthdate),
          grade(grade), cls(cls), dept(dept), major(major) {}

<<<<<<< HEAD
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

    // 设置学生班级和专业的方法
    void setInfo(string cls, string major)
    {
        this->cls = cls;     // 设置学生班级
        this->major = major; // 设置学生专业
=======
    // ��ʾѧ����Ϣ
    void show()
    {
        cout << "ѧ�ţ�" << id << endl;
        cout << "������" << name << endl;
        cout << "�Ա�" << gender << endl;
        cout << "�������ڣ�" << birthdate << endl;
        cout << "�꼶��" << grade << endl;
        cout << "�༶��" << cls << endl;
        cout << "Ժϵ��" << dept << endl;
        cout << "רҵ��" << major << endl;
    }

    // �޸�ѧ����Ϣ
    void setInfo(string cls, string major)
    {
        this->cls = cls;
        this->major = major;
>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    }
};

int main()
{
<<<<<<< HEAD
    Student students[5]; // 创建一个包含5个学生对象的数组

    for (int i = 0; i < 5; i++)
    {
        cout << "Input NO." << i + 1 << " Student's info " << endl;
        string id, name, gender, birthdate, grade, cls, dept, major;

        cout << "Input ID:\t\t";
        getline(cin, id); // 获取学生ID

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

        students[i] = Student(id, name, gender, birthdate, grade, cls, dept, major); // 使用获取的信息创建学生对象并将其存储在数组中
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "Showing the NO." << i + 1 << " student's info" << endl;
        students[i].show(); // 显示学生信息
        cout << endl;
    }

=======
    // ʹ�ö������鱣��ѧ������
    Student students[5];

    // �Ӽ�������ѧ����Ϣ�����ô������Ĺ��캯������ѧ������
    for (int i = 0; i < 5; i++)
    {
        cout << "������ѧ��������Ϣ��" << endl;
        string id, name, gender, birthdate, grade, cls, dept, major;
        cout << "ѧ�ţ�";
        getline(cin, id);
        cout << "������";
        getline(cin, name);
        cout << "�Ա�";
        getline(cin, gender);
        cout << "�������ڣ�";
        getline(cin, birthdate);
        cout << "�꼶��";
        getline(cin, grade);
        cout << "�༶��";
        getline(cin, cls);
        cout << "Ժϵ��";
        getline(cin, dept);
        cout << "רҵ��";
        getline(cin, major);

        students[i] = Student(id, name, gender, birthdate, grade, cls, dept, major);
    }

    // ��ʾѧ����Ϣ
    for (int i = 0; i < 5; i++)
    {
        cout << "�� " << i + 1 << " ��ѧ������Ϣ��" << endl;
        students[i].show();
        cout << endl;
    }

    // �޸�ѧ����Ϣ
    string cls, major;
    cout << "������Ҫ�޸ĵ�ѧ���İ༶��רҵ��" << endl;
    cout << "�༶��";
    getline(cin, cls);
    cout << "רҵ��";
    getline(cin, major);

    students[0].setInfo(cls, major);

    cout << "�޸ĺ��ѧ����Ϣ��" << endl;
    students[0].show();

>>>>>>> 4b973315162d27f01fa06261e78d6fb1c889420e
    return 0;
}
