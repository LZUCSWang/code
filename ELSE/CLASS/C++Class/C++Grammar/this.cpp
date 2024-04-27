#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Person
{
public:
    static int age;
    string name;
    static void func();
    void func1();
    Person &operator=(const Person &p)
    {
        cout << "Person& operator=(const Person& p)" << endl;
        age = p.age;
        name = p.name;
        return *this;
    }

private:
    int wife;
};
int Person::age = 10;
void Person::func()
{
    cout << "func()" << endl;
    cout << age << endl;
    // cout << name << endl;
    // cout << wife << endl;
}
void Person::func1()
{
    cout << "func1()" << endl;
}
int main()
{
    Person p;
    Person p1;
    p1 = p;
    p.func1();
    p.func();
    return 0;
}