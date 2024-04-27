#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
// void friendfun(Person *per);
class Person;
class friendclass
{
public:
    friendclass();
    void visitPerson();

private:
    Person *per;
};
class Person
{
    friend class friendclass;
    friend void friendfun(Person *per); //全局函数做友元

public:
    Person()
    {
        age = 0;
        name = "王";
    }
    string name;

private:
    int age;
};
void friendclass::visitPerson()
{
    cout << "friendclass visit" << per->age << endl;
}
friendclass::friendclass()
{
    per = new Person;
}
void friendfun(Person *per)
{
    per->age = 100;
    cout << "friendfun()" << endl;
}

int main()
{
    friendclass fc;
    fc.visitPerson();
    // friendclass fc;
    // fc.visitPerson(&p);
    return 0;
}
