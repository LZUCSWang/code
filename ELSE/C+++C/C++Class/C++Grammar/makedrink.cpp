#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class AbstractDrinking
{
public:
    virtual void Boil() = 0;
    virtual void Brew() = 0;
    virtual void Pour() = 0;
    virtual void PutSome() = 0;
    void makeDrink()
    {
        Boil();
        Brew();
        Pour();
        PutSome();
    }
};

class Coffee : public AbstractDrinking
{
public:
    virtual void Boil()
    {
        cout << "zhu" << endl;
    }
    virtual void Brew()
    {
        cout << "chongpao" << endl;
    }
    virtual void Pour()
    {
        cout << "daoru" << endl;
    }
    virtual void PutSome()
    {
        cout << "fangniunai" << endl;
    }
};

void dowork(AbstractDrinking *drink)
{
    drink->makeDrink();
    delete drink;
}

void test1()
{
    Coffee *coffee = new Coffee;
    dowork(coffee);
}

int main()
{
    test1();
}