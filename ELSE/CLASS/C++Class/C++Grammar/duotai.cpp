#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long
class Animal
{
public:
    virtual void speak()
    {
        cout << "talk" << endl;
    }
};
class Cat : public Animal
{
public:
    void speak()
    {
        cout << "Cat talk" << endl;
    }
};
class Dog : public Animal
{
public:
    void speak()
    {
        cout << "Dog talk" << endl;
    }
};
//地址早绑定
void dospeak(Animal &animal)
{
    animal.speak();
}

void test1()
{
    Cat cat;
    dospeak(cat);
    Dog dog;
    dospeak(dog);
}
void test2()
{
    cout << sizeof(Animal) << endl;
}
int main()
{
    test2();
    test1();
}