#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
class Phone
{
public:
    Phone()
    {
        cout << "Phone()" << endl;
    }
    Phone(string name)
    {
        cout << "Phone(string name)" << endl;
        m_strName = name;
    }
    Phone(const Phone &p)
    {
        cout << "Phone(const Phone& p)" << endl;
        m_strName = p.m_strName;
    }
    ~Phone()
    {
        cout << "~Phone()" << endl;
    }
    string m_strName;
};
class Person
{
public:
    Phone m_Phone;
    Person(string name, string Pname) : name(name), m_Phone(Pname)
    {
        cout << "Person(string name,string Pname)" << endl;
    }
    Person()
    {
        cout << "�޲�Ĭ�Ϲ���" << endl;
    }
    Person(int a)
    {
        cout << "�вι���" << endl;
        age = a;
    }
    // Person(int a) : age(a) {}
    Person(const Person &p)
    {
        cout << "��������" << endl;
        age = p.age;
    }
    int age;
    string name;
};

void test0()
{
    Person p1(1);
    cout << p1.age << endl;
    Person p2(p1);
    cout << p2.age << endl;
}
int main()
{
    test0();
}
