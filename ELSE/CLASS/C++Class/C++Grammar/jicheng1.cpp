#include <bits/stdc++.h>
using namespace std;
#define N 1e5
#define INF 2e9
#define MAX 10000000
#define ll long long

class Base1
{
public:
    int m_A;

protected:
    int m_B;

private: //�޷��̳�
    int m_C;
};
class son1 : public Base1
{
public:
    void fun()
    {
        m_A = 10;
        m_B = 10;
        cout << m_A << endl;
        cout << m_B << endl;
    }
    int m_D;
};
class son2 : protected Base1
{
public:
    void fun()
    {
        m_A = 10;
        m_B = 10;
        cout << m_A << endl;
        cout << m_B << endl;
    }
};
class son3 : private Base1
{
public:
    void fun()
    {
        m_A = 10;
        m_B = 10;
        cout << m_A << endl;
        cout << m_B << endl;
    }
};
class son4 : public son3
{
public:
    void fun()
    {
        // m_A = 10;
    }
};
class son1class
{
public:
    son1 s1;
    // s1.m_A;
};
void test1()
{
    son1 s1;
    s1.m_A = 10;
    s1.fun();
    cout << sizeof(s1) << endl;
    //�̳е�ʱ��˽�м̳в��ˣ��������ڸ����еĳ�Ա�����õ��˸����е�˽�����ԣ�����˽�е�Ҳ�̳��ˣ�ֻ�Ƿ��ʲ���
    son2 s2;
    // s2.m_A = 10;
    s2.fun();
    // s1.m_B=10
}
int main()
{
    test1();
    // son1 s1;
    return 0;
}