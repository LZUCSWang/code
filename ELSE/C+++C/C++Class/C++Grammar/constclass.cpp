#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Person
{
public:
    int m_A;
    mutable int m_B;
    Person()
    {
        m_A = m_B = 0;
    }
    void showPerson() const
    {
        // this->m_A = 100;
        this->m_B = 100;
        cout << "m_A = " << m_A << endl;
        cout << "m_B = " << m_B << endl;
    }
};

int main()
{
    Person p;
    p.showPerson();
    const Person cp;
    cp.showPerson();
    cp.m_B = 1000;
    cp.showPerson();
    return 0;
}