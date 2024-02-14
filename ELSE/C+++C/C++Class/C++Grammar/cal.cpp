#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Calculator
{
public:
    int getResult(string oper)
    {
        if (oper == "+")
            return m_Num1 + m_Num2;
        if (oper == "-")
            return m_Num1 - m_Num2;
        if (oper == "*")
            return m_Num1 * m_Num2;
        return -1;
    }
    int m_Num1;
    int m_Num2;
};

class BaseCal
{
public:
    virtual int getResult()
    {
        return 0;
    }
    int m_N1, m_N2;
};
class Cal : public BaseCal
{
public:
};
void test1()
{
    Calculator c;
    c.m_Num1 = 10;
    c.m_Num2 = 10;
    cout << c.getResult("+") << endl;
}
int main()
{
    test1();
}