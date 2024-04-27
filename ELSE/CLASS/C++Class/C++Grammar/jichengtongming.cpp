#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Base
{
public:
    int m_A;
    Base()
    {
        m_A = 100;
    }
};
class son : public Base
{
public:
    son()
    {
        m_A = 200;
    }
    int m_A;
};

void test1()
{
    son s;
    cout << s.m_A << endl;
    cout << s.Base::m_A << endl;
}

int main()
{
    test1();
}