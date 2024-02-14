#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Base
{
public:
    Base()
    {
        cout << "father make " << endl;
    }
    ~Base()
    {
        cout << "father destroy" << endl;
    }
};

class son : public Base
{
    son()
    {
        cout << "son make " << endl;
    }
    ~son()
    {
        cout << "son destroy" << endl;
    }
};

void test1()
{
    // Base b;
    son s();
    //创建子类对象的同时会创建父类对象。
    //继承中的构造和析构顺序
    //现有父亲后有儿子，白发人送黑发人

}
int main()
{
    test1();
}